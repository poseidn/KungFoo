#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentEngine/src/StateEngine/StateChangeInfo.h>

class GameState;

class StartGameAspect: public Aspect<GameState> {
public:
	StartGameAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	void onActivate(GameState & gs, StateChangeInfoPtr const&);
	void onDeactivate(GameState & gs);
	void onOpenMenu(GameState & gs);
};
