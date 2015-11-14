#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include <DescentEngine/src/Input/InputContainer.h>

// translates the content of an InputContainer
// to the signals of a game state

template<class TState>
class DebugFunctionAspect: public Aspect<TState> {
public:
	DebugFunctionAspect() {
	}

	virtual ~DebugFunctionAspect() {
	}

	virtual void init(TState & gs) CPP11_OVERRIDE
	{
		gs.slotDebugSwitchRenderTiles.subscribe([] ( TState & g, bool b)
		{/*
		 if (g.getEngines().inputEngine().any_keyDownExit().first) {
		 g.requestApplicationQuit();
		 }*/
			g.getEngines().renderEngine().setDebugFaces(
					! g.getEngines().renderEngine().getDebugFaces( ));

		});
	}

};
