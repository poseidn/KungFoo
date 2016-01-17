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
class InputMenuAspect: public Aspect<TState> {
public:

	// todo : virtual decstructor for all aspects !
	InputMenuAspect() {
	}

	virtual void init(TState & gs) CPP11_OVERRIDE
	{
		gs.slotStep.subscribe([=] ( TState & g, float t)
		{	this->step(g,t);});
	}

	void step(TState & gs, float deltaT) {

		const float ButtonTimeout = 0.3f;
		const float MoveTimeout = 0.12f;

		m_stickMoved.validate(deltaT, 0.0f);
		m_kick.validate(deltaT, 0.0f);
		m_jump.validate(deltaT, 0.0f);

		InputSystem & inp = gs.getEngines().inputEngine();

		const auto kickRes = inp.any_keyDownKick();
		if (kickRes.first && m_kick.canActivate()) {
			m_kick.activate(ButtonTimeout);
			gs.slotInputSelect.signal(gs, kickRes.second);
		}

		const auto jumpRes = inp.any_keyDownJump();
		if (jumpRes.first && m_jump.canActivate()) {
			m_jump.activate(ButtonTimeout);
			gs.slotInputEnable.signal(gs, jumpRes.second);
		}

		const auto stickRes = inp.any_isStickOneMoved();
		if (stickRes.first && m_stickMoved.canActivate()) {
			auto stickDir = inp.any_directionStickOne();
			Vector2 stickMove(stickDir.first);

			if (stickMove.y() > 0.0f) {
				m_stickMoved.activate(MoveTimeout);
				gs.slotInputMove.signal(gs, MenuState::MovementDirection::Up, stickDir.second);
			}
			if (stickMove.y() < 0.0f) {
				m_stickMoved.activate(MoveTimeout);
				gs.slotInputMove.signal(gs, MenuState::MovementDirection::Down, stickDir.second);
			}
		}
	}
private:
	TimeSliceAction m_stickMoved;
	TimeSliceAction m_kick;
	TimeSliceAction m_jump;
};
