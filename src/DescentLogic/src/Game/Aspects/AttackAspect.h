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

#pragma once

#include <list>

#include <DescentEngine/src/VectorTypes.h>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include "../PlayerData.h"

class GameState;

class AttackAspect: public Aspect<GameState> {
public:
	AttackAspect() {
	}

	virtual ~AttackAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	void step(GameState & gs, const float deltaT);

	template<class TAttackingEntity, class TAttackedEntity, class TActionLambda>
	void attackOnList(TAttackingEntity * attacking, std::list<TAttackedEntity *> entityList,
			TActionLambda actionLambda, PlayerData * player, float attackAngle, float attackRange,
			float hitTime, size_t maxAffectCount) {
		size_t affectCount = 0;
		for (auto & enemy : entityList) {
			// disable, we cannot place enough hits in the short amount of time the enemy
			// is in front of us
			/*if (enemy->getHitAction().isActive())
			 continue;*/
			auto conVector = enemy->getPosition() - attacking->getPosition();

			if (!enemy->isDead() && (conVector.magSquared() < attackRange)) {
				// check for correction direction
				const Vector2 conVec = enemy->getPosition() - attacking->getPosition();
				const float angle = Vector2::angleBetween(conVec, attacking->getDirection());

				if (angle < attackAngle) {

					actionLambda(attacking, enemy, player, conVec);
				}
				// only once kick an enemy
				affectCount++;
				if (affectCount >= maxAffectCount)
					break;
			}

		}
	}
};
