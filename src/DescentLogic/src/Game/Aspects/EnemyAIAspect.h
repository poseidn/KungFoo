#pragma once

#include <list>
#include <functional>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

class GameState;
class PlayerEntity;

class EnemyAIAspect: public Aspect<GameState> {
public:
	EnemyAIAspect() :
			m_bEnemyAttack(true) {
	}

	virtual ~ EnemyAIAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

	void switchScrolling(GameState & gs) {
		// don't make do this right now, because the enemies will not attack if
		// the app is started up with no scrolling
		//m_bEnemyAttack = !m_bEnemyAttack;
	}
private:
	void step(GameState & gs, const float deltaT);
	bool m_bEnemyAttack;

};
