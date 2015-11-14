#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentEngine/src/TickAction.h>

class GameState;

class ScoringAspect: public Aspect<GameState> {
public:
	ScoringAspect() :
			m_increaseScoreTick(1.0f) {
	}

	virtual ~ScoringAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	TickAction m_increaseScoreTick;
};
