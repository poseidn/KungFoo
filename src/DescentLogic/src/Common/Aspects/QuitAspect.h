#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include <DescentEngine/src/Input/InputContainer.h>

// translates the content of an InputContainer
// to the signals of a game state

template<class TState>
class QuitAspect: public Aspect<TState> {
public:
	QuitAspect() {
	}

	virtual ~QuitAspect() {
	}

	virtual void init(TState & gs) CPP11_OVERRIDE
	{
		gs.slotStep.subscribe([] ( TState & g, float t)
		{
			if (g.getEngines().inputEngine().any_keyDownExit().first) {
				g.requestApplicationQuit();
			}

		});
	}

};
