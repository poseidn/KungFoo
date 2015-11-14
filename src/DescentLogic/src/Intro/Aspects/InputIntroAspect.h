#pragma once

#include <DescentEngine/src/EntityEngine/TimeSliceAction.h>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include <DescentEngine/src/Input/InputContainer.h>
#include <DescentEngine/src/EntityEngine/EntityFactory.h>
#include <DescentLogic/src/Entities/WallEntity.h>

#include <DescentLogic/src/Menu/MenuState.h>

// translates the content of an InputContainer
// to the signals of a game state

template<class TState>
class InputIntroAspect: public Aspect<TState> {
public:
	

	InputIntroAspect() {
	}

	virtual ~InputIntroAspect() {
	}

	virtual void init(TState & gs) CPP11_OVERRIDE
	{
		gs.slotStep.subscribe([=] ( TState & g, float t)
		{	this->step(g,t);});
	}

	void step(TState & gs, float deltaT) {

		const float ButtonTimeout = 0.8f;

		m_kick.validate(deltaT, 0.0f);

		InputSystem & inp = gs.getEngines().inputEngine();

		const auto kickRes = inp.any_keyDownKick();
		if (kickRes.first && m_kick.canActivate()) {
			m_kick.activate(ButtonTimeout);
			gs.slotInputNext.signal(gs, kickRes.second);
		}

	}
private:
	TimeSliceAction m_kick;
};
