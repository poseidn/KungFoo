#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentEngine/src/StateEngine/StateChangeInfo.h>

class GameState;

class RemoveEntitiesAspect: public Aspect<GameState> {
public:
	RemoveEntitiesAspect() {
	}

	virtual ~RemoveEntitiesAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

};
