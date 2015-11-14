#pragma once

#include <boost/noncopyable.hpp>

#include "../Cpp11.h"
#include "InputSystemBase.h"
#include "InputContainer.h"

#include "NullInput.h"

// this class will allow two input system to operate on the
// same InputContainer instead of one,
// can be used to have dummy input from the application fed back
// to the whole game stack
template<class TInputA, class TInputB = NullInput, class TInputC = NullInput>
class MultiplexedInput: public InputSystemBase {
public:
	MultiplexedInput(TInputA * iA, TInputB * iB = nullptr, TInputC * iC = nullptr) :
			m_inputA(iA), m_inputB(iB), m_inputC(iC) {

	}

	virtual void updateContainer(float deltaT) CPP11_OVERRIDE
	{
		auto & cont(getContainers());

		for (auto & c : cont) {
			c.second.resetKeypress();
		}
		// hand to the sub inputs
		if (m_inputA)
			m_inputA->updateContainer(cont, deltaT);

		if (m_inputB)
			m_inputB->updateContainer(cont, deltaT);

		if (m_inputC)
			m_inputC->updateContainer(cont, deltaT);
	}

	DeviceList availableInputDevices() const {
		DeviceList dlOne = m_inputA->availableInputDevices();

		return dlOne;
	}

	size_t maxInputDevices() const {
		return m_inputA->maxInputDevices();
	}

private:
	TInputA * m_inputA;
	TInputB * m_inputB;
	TInputC * m_inputC;
};

