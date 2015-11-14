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
