#include "DisplayEventsAspect.h"

#include <sstream>
#include <algorithm>

#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/Visuals/TextSupport.h>
#include <DescentEngine/src/RandomEngine.h>
#include <DescentLogic/src/Entities/EnemyEntity.h>
#include <DescentLogic/src/Config/GameRules.h>
#include <DescentLogic/src/Entities/PlayerEntity.h>

#include "../GameState.h"

#include "../../Common/GameToMenuInfo.h"

void DisplayEventsAspect::init(GameState & gameState) {
	gameState.slotEnemyDied.subscribe([ ] ( GameState & g, PlayerId pid, EnemyEntity * pEnt )
	{
		std::stringstream cmbText;
		cmbText << " " << GameRules::PointsForKill << " ";
		TextSupport::ingameTextFadeOut( g.getEngines(),
				g.getEngines().randomEngine().randomAbovePoint(
						pEnt->getPosition(), 1.5f ), cmbText.str());
	});

	gameState.slotComboDone.subscribe([ ] (GameState & g,PlayerId pid,int enemiesKilld,
			int points, ComboType cmbType ) {
		std::stringstream cmbText;
		cmbText << enemiesKilld << " Combo: " << points;
		PlayerEntity * pEnt = g.getPlayerEntity( pid );
		TextSupport::ingameTextFadeOut( g.getEngines(), g.getEngines().randomEngine().randomAbovePoint(
						pEnt->getPosition(), 1.5f ), cmbText.str(), 1.2f );
	});
}

