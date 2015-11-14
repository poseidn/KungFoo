#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

class GameState;

class DisplayEventsAspect: public Aspect<GameState> {
public:
	DisplayEventsAspect() {
	}

	virtual ~DisplayEventsAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

};
