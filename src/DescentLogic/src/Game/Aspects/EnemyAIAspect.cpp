/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "EnemyAIAspect.h"

#include <DescentEngine/src/Log.h>
#include "../../Config/EnemyBehaviour.h"
#include "../../Config/PlayerMovement.h"
#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"
#include "../../Entities/EnemyEntity.h"

void EnemyAIAspect::init(GameState & gs) {
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);}, "EnemyAIAspect.step");

	gs.slotDebugSwitchScrolling.subscribe([this ]( GameState & g, bool enabled)
	{	this->switchScrolling(g);});
}

void EnemyAIAspect::step(GameState & gs, const float deltaT) {

	// check which enemies are near to the player and let them attack
	for (EnemyEntity * enemy : gs.getEnemies()) {
		if (enemy->isDead())
			continue;

		// first thing, handle the actions
		enemy->validateActions(deltaT, EnemyBehaviour::HitTime);
		enemy->updateVisual(gs.getEngines());

		// check distance to the closest player
		float closestDist = 10000000.0f;
		PlayerEntity * playerEnt = nullptr;

		for (PlayerData & pd : gs.getPlayers()) {
			if (nullptr != pd.Entity) {
				const float distSq = (enemy->getPosition() - pd.Entity->getPosition()).magSquared();
				if (distSq < closestDist) {
					closestDist = distSq;
					playerEnt = pd.Entity;
				}
			}
		}

		if (playerEnt != nullptr) {
			if (m_bEnemyAttack && !enemy->isLyingFlat() && enemy->decreaseLastHit(deltaT)) {
				if (!enemy->isAttacking()) {
					// check how far this one is from the player
					// todo: use line of sight here

					if (closestDist < EnemyBehaviour::AttackSquaredDistancePlayer) {
						// move towards player
						enemy->startAttack();
						logging::Info() << "Enemy starting attack";
					}
				} else {
					//
					//if (enemy->checkAttackTimeout(deltaT)) {

					if (closestDist > EnemyBehaviour::StopAttackSquaredDistancePlayer) {
						// the enemy is too far, stop the attack
						// it will restart the attack in the next round if another player
						// is close by
						enemy->stopAttack();
						continue;
					}

					// move towards player
					const float dist = enemy->runTo(playerEnt->getPosition(), enemy->getMaxSpeed(), deltaT,
							gs.getEngines().entityEngine(), EnemyBehaviour::ClosestApproach);

					// are we close ? if so, attack !!
					if (dist < EnemyBehaviour::KickDistancePlayer) {
						// for for the attack time
						if (enemy->getAttackTime() < 0.0f) {
							enemy->getKickAction().activate(PlayerMovement::KickTime);
						} else {
							enemy->decreaseAttackTime(deltaT);
						}
					}
					//}
				}
			}
		}
	}
}

