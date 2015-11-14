#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

class GameState;
class LevelFactory;

class ForwardScrollingAspect: public Aspect<GameState> {
public:
	ForwardScrollingAspect(bool scrollEnabled = true) :
			m_scrollEnabled(scrollEnabled) {
	}

	virtual ~ForwardScrollingAspect() = default;

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	void step(GameState & gs, const float deltaT);
	void switchScrolling(GameState & gs);
	bool m_scrollEnabled;

};
