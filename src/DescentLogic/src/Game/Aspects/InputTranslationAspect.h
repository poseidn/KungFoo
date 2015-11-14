#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include <DescentEngine/src/Input/InputSystem.h>
#include <DescentEngine/src/Input/InputContainer.h>
#include <DescentEngine/src/EntityEngine/EntityFactory.h>
#include <DescentLogic/src/Entities/WallEntity.h>

#include "../PlayerData.h"

// translates the content of an InputContainer
// to the signals of a game state

template<class TState>
class InputTranslationAspect: public Aspect<TState> {
public:
	// todo : virtual decstructor for all aspects !
	InputTranslationAspect() {
	}

	virtual ~InputTranslationAspect() {
	}

	virtual void init(TState & gs) CPP11_OVERRIDE
	{
		gs.slotStep.subscribe([=] ( TState & g, float t)
		{	this->step(g,t);});
	}

	void step(TState & gs, float deltaT) {
		InputSystem & inpSystem = gs.getEngines().inputEngine();

		for (PlayerData & pd : gs.getPlayers()) {
			// todo: protect against player ids which have not been assigned an input container
			InputContainer const& inp = inpSystem.getContainerConst(pd.Id);
			//std::cout << "inp p " << pd.Id << std::endl;

			if (inp.keyPressDebug1()) {
				gs.slotDebugSwitchScrolling.signal(gs, true);
			}

			if (inp.keyPressDebug2()) {
				gs.slotDebugSwitchRenderTiles.signal (gs, true);
			}

			if (inp.isStickOneMoved()) {
				gs.slotPlayerMove.signal(gs, inp.directionStickOne(), pd.Id);
			}

			if (inp.keyDownMenu()) {
				gs.slotOpenMenu.signal(gs);
			}

			if (inp.keyDownJump()) {
				gs.slotPlayerJump.signal(gs, pd.Id);
			}

			if (inp.keyDownKick()) {
				gs.slotPlayerKick.signal(gs, pd.Id);
			}

			for (auto const& s : inp.m_inputKeys) {
				if (s == "r") {
					//gs.slot
					gs.loadTestFragment();

				}
				if (s == "c") {
					logging::Info() << "cleaning";
					gs.clearAllStaticEntities();
				}
			}

			/// make this coming from the special move detection
			if (inp.keyDownBiking()) {
				gs.slotPlayerSpecialMove.signal(gs, pd.Id);
			}

		}
	}

};
