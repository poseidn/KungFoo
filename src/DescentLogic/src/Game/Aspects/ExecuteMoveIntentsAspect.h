#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

class GameState;

//* not needed any more, done by EntityEngine

class ExecuteMoveIntentsAspect: public Aspect<GameState> {
public:
	ExecuteMoveIntentsAspect() {
	}

	virtual ~ExecuteMoveIntentsAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	void step(GameState & gs, const float deltaT);

};
