#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/VectorTypes.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

class GameState;
class LevelFactory;

class FreeScrollingAspect: public Aspect<GameState> {
public:
	FreeScrollingAspect() {
	}

	virtual ~FreeScrollingAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	void playerMove(GameState & gs, Vector2 const& v);

	void step(GameState & gs, const float deltaT);

};
