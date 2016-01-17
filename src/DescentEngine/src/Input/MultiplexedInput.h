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

