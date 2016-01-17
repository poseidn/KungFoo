#include "MovePlayerAspect.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <DescentEngine/src/VectorTypes.h>
#include <DescentEngine/src/ResourceEngine/ResourceEngine.h>
#include <DescentEngine/src/Util.h>
#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/SoundEngine/SoundEngine.h>

#include "../GameState.h"
#include "../../Config/PlayerMovement.h"
#include "../../Config/VibratePatterns.h"
#include "../../Config/GameMovement.h"

#include "../../Entities/PlayerEntity.h"

#include "../../Entities/TextureIds.h"

void MovePlayerAspect::init(GameState & gs) {
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);}, "MovePlayerAspect.step");

	gs.slotPlayerMove.subscribe(
			[this] ( GameState & g, Vector2 const& v, PlayerId id )
			{	this->playerMove(g,v, id);});

	gs.slotPlayerJump.subscribe([this] ( GameState & g, PlayerId id )
	{	this->playerJump(g, id);});

	gs.slotPlayerKick.subscribe([this] ( GameState & g, PlayerId id )
	{	this->playerKick(g, id);});

	gs.slotPlayerSpecialMove.subscribe([this] ( GameState & g, PlayerId id )
	{	this->playerBiking(g, id);});

	gs.slotDebugSwitchScrolling.subscribe([this ]( GameState & g, bool enabled)
	{	this->switchScrolling(g,enabled);});
}

// todo: also have an acceleration phase to allow for more precise, smaller
// movements
void MovePlayerAspect::step(GameState & gs, float deltaT) {
	for (PlayerData & pd : gs.getPlayers()) {
		// no movement if player is dead !
		if (pd.IsDead)
			continue;

		PlayerEntity * pent = pd.Entity;

		// make sure this exists, if not, create
		if (m_movements.find(pd.Id) == m_movements.end())
			m_movements[pd.Id] = Movements();

		Movements & mov = m_movements[pd.Id];

		if (pent == nullptr)
			continue;

		const float maxSpeed = PlayerMovement::MaxSpeed * deltaT;
		//logging::Debug() << "maxSpeed is " << maxSpeed;

		// limit the overall movement to the maximum player speed
		mov.m_stepMovement = mov.m_stepMovement.limitedCopy(maxSpeed);

		float resMovementMag = mov.m_residualMovement.mag();
		/*logging::Debug() << "residual before reduction is " << std::setprecision(4)
		 << resMovementMag;*/

		const float movementDecay = computeMovementDecay(maxSpeed,
				resMovementMag); // 2.0f per second
		// apply decay
		resMovementMag = resMovementMag - movementDecay * deltaT;
		resMovementMag = std::max(0.0f, resMovementMag);

		//logging::Debug() << "residual is " << std::setprecision(4) << resMovementMag;
		mov.m_residualMovement = mov.m_residualMovement.normalizedCopy()
				* resMovementMag;

		// combine
		Vector2 thisMovement = mov.m_stepMovement + mov.m_residualMovement;

		thisMovement = thisMovement.limitedCopy(maxSpeed);
		// limit the

		auto lmbDirection = [&pent, &gs] () -> float {
			CPP11_CONSTEXPR float maxDirection = 0.9f;

			// compute player location
				float direction = pent->getPosition().x()
				/ gs.getEngines().renderEngine().getScreenTransform().screenSizeInTiles().x();
				// shift to -0.7 to 0.7
				direction = (direction * maxDirection * 2.0f) - maxDirection;
				return direction;
			};

		util::RunOnce<decltype( lmbDirection), float> direction(lmbDirection);

		// init jump, if needed
		pent->validateActions(deltaT, PlayerMovement::HitRegenTime);

		if (mov.m_jumpInit && pent->getJumpAction().canActivate()) {
			auto snd = gs.getEngines().resourceEngine().loadSound(
					"player_jump1");
			gs.getEngines().soundEngine().startVibratePattern(
					VibratePatterns().PlayerJump);
			gs.getEngines().soundEngine().playSound(snd, direction.result());
			pent->getJumpAction().activate(PlayerMovement::JumpTime);

			pent->setCollisionGroup(GameCollisionGroups::CharactersJump);
			pent->setCollisionMask(
					GameCollisionGroups::CharactersJump_CollidesWith);
		}

		if (pent->getJumpAction().wasJustDisabled()) {
			// set back to no jump mode, if necessary
			pent->setCollisionGroup(GameCollisionGroups::Characters);
			pent->setCollisionMask(
					GameCollisionGroups::Characters_CollidesWith);
		}

		if (mov.m_kickInit && pent->getKickAction().canActivate()) {
			// make this more event base
			// disabled because the sounds seems not to load
			auto snd = gs.getEngines().resourceEngine().loadSound(
					"player_kick1");
			gs.getEngines().soundEngine().playSound(snd, direction.result());

			pent->getKickAction().activate(PlayerMovement::KickTime);

			mov.m_kickCount++;

			if (mov.m_kickCount > 9) {
				mov.m_kickCount = 0;
				auto randPick = m_randDist(m_randEngine);
				std::stringstream soundName;
				soundName << "player_yell" << randPick << "";

				// disabled because the sounds seems not to load
				auto snd = gs.getEngines().resourceEngine().loadSound(
						soundName.str());
				gs.getEngines().soundEngine().playSound(snd,
						direction.result());
			}
		}

		// todo: check no other actions are running or cancel them ...
		if (mov.m_bikingInit && pent->getBikingAction().canActivate()) {
			pent->getBikingAction().activate(PlayerMovement::BikingTime);
			// we only move forward with this move !

		}

		mov.m_stepMovement = Vector2::Zero();
		mov.m_jumpInit = false;
		mov.m_kickInit = false;
		mov.m_bikingInit = false;

		if (pent->getJumpAction().isActive())
			thisMovement = thisMovement
					* PlayerMovement::JumpIncreaseSpeedFactor;

		// store for next rounds .. this has to done before the scrolling speed increase
		// otherwise the speed is too fast...
		mov.m_residualMovement = thisMovement;

		if (gs.getScrollActive() && m_scrollEnabled
				&& !pent->getBikingAction().isActive()) {
			thisMovement = thisMovement
					+ Vector2::UnitY() * GameMovement::ScrollSpeed * deltaT;
			// limit the y-speed sepaeretley, because we added the scroll speed
			// should always be positive, the player can not stand still
			// allow a bit more speed in this direction, using the factor 1.2
			thisMovement.setY(std::min(thisMovement.y(), maxSpeed * 1.2f));
			//thisMovement.setY(thisMovement.y());
		}

		// todo: move this into a more general entity-walkable class
		//logging::Debug() << "this movement is " << std::setprecision(4) << thisMovement.mag();

		if (pent->getBikingAction().isActive()) {
			// limit sideway movement
			//thisMovement.setX(thisMovement.x() * 0.2f);
			thisMovement.setX(
					thisMovement.x() * PlayerMovement::BikingMaxMovement);
			thisMovement.setY(GameMovement::ScrollSpeed * deltaT * 1.1f);
			pent->setDirection(Vector2::UnitY());
		}

		// check the sector
		if (thisMovement.magSquared() > 0.0000001f) {
			auto dir = thisMovement.normalizedCopy();
			pent->setDirection(dir);
		}

		// limit the players upward movement, so he can not run out of the screen at the top
		const auto camLocation =
				gs.getEngines().renderEngine().getCameraLocation();
		if ((pent->getPosition().y()
				> (camLocation.y() + PlayerMovement::MaxAdvance))
				&& (thisMovement.y() > 0.0f)) {
			if (m_scrollEnabled && gs.getScrollActive()) {
				thisMovement.setY(GameMovement::ScrollSpeed * deltaT * 0.8f);
			} else {
				thisMovement.setY(0.0f);
			}
		}

		pent->updateVisual(gs.getEngines());
		pent->deltaMoveIntent(thisMovement);
	}
}

float MovePlayerAspect::computeMovementDecay(const float maxSpeed,
		const float resSpeed) {
	/*const float ratio = resSpeed / maxSpeed;*/

	return /*ratio * PlayerMovement::MovementDecayDynamic +*/PlayerMovement::MovementDecayStatic;
}

void MovePlayerAspect::playerBiking(GameState & gs, PlayerId id) {
	m_movements[id].m_bikingInit = true;
}

void MovePlayerAspect::playerMove(GameState & gs, Vector2 const& vec,
		PlayerId id) {
	m_movements[id].m_stepMovement = m_movements[id].m_stepMovement + vec;

//m_stepMovement = m_stepMovement + vec;
}

void MovePlayerAspect::playerJump(GameState & gs, PlayerId id) {
	m_movements[id].m_jumpInit = true;

}

void MovePlayerAspect::playerKick(GameState & gs, PlayerId id) {
	m_movements[id].m_kickInit = true;

}

void MovePlayerAspect::switchScrolling(GameState & gs, bool enabled) {
	m_scrollEnabled = !m_scrollEnabled;
}

