/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

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
			StateBase(), m_engines(eg) {

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
	// skip the first stage with the company logo and move
	// directly to the Kung Foo intro
	size_t m_stage = 1;

};
