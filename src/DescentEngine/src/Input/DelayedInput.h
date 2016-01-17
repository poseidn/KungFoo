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

#include <boost/noncopyable.hpp>
#include <list>

//#include "InputContainer.h"

class DelayedInput: private boost::noncopyable {
public:
	class InputCommand {
	public:
		enum class ActionEnum {
			Kick, Jump, Exit
		};

		InputCommand(ActionEnum act, float tstamp) :
				Action(act), Timestamp(tstamp), Done(false) {

		}

		const ActionEnum Action;
		const float Timestamp;
		bool Done;
	};

	void updateContainer(InputSystemBase::ContainerArray & containers, float deltaT) {
		/*	m_integratedTime += deltaT;

		 for (auto & ic : m_inputCommands) {
		 if (!ic.Done && (ic.Timestamp < m_integratedTime)) {
		 ic.Done = true;

		 //
		 if (ic.Action == InputCommand::ActionEnum::Kick) {
		 container.setKeyDownKick(true);
		 } else if (ic.Action == InputCommand::ActionEnum::Jump) {
		 container.setKeyDownJump(true);
		 } else if (ic.Action == InputCommand::ActionEnum::Exit) {
		 container.setKeyDownExit(true);
		 } else {
		 logging::Fatal() << "DelayedInput: Action item not supported";
		 }
		 }
		 }*/
	}

	void addCommand(InputCommand const& cmd) {
		m_inputCommands.push_back(cmd);
	}

private:
// will be very imprecise over a long amount of time
//	float m_integratedTime; put this in constructor
	std::list<InputCommand> m_inputCommands;
};

