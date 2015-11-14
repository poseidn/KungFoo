#pragma once

#include <list>

#include <boost/noncopyable.hpp>

#include <DescentEngine/src/Input/InputSystem.h>
#include <DescentEngine/src/Signals.h>
#include <DescentEngine/src/Engines.h>

#include <DescentEngine/src/StateEngine/StateBase.h>

#include <DescentEngine/src/EntityEngine/Entity.h>

class InputContainer;

class IntroState: public StateBase {
public:
	enum class MovementDirection {
		Up, Down
	};

	IntroState(Engines & eg) :
			StateBase(), m_engines(eg), m_stage(0) {

	}

	virtual ~IntroState() {
	}

	slots::Slot<IntroState &, float> slotStep;

	slots::Slot<IntroState &, StateChangeInfoPtr const&> slotActivateState;
	slots::Slot<IntroState &> slotDeactivateState;

	slots::Slot<IntroState &, InputSystem::ContainerId> slotInputNext;
	slots::Slot<IntroState &, bool> slotDebugSwitchRenderTiles;
	/* slots::Slot<MenuState &, InputSystem::ContainerId> slotInputEnable;
	 slots::Slot<MenuState &, MovementDirection, InputSystem::ContainerId> slotInputMove;
	 */

	virtual void onActivateState(StateChangeInfoPtr const& changeInfo) CPP11_OVERRIDE {
		slotActivateState.signal(*this, changeInfo);
	}

	virtual void onDeactivateState() CPP11_OVERRIDE {
		slotDeactivateState.signal(*this);
	}

	Engines & getEngines() {
		return m_engines;
	}

	size_t getStage() const {
		return m_stage;
	}

	void setStage(size_t s) {
		m_stage = s;
	}

	ManagedEntityList m_managedEntities;

private:
	Engines & m_engines;
	size_t m_stage;

};
