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

