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
#include <vector>

#include "../SDL_include.h"

#include "../Log.h"
#include "../Cpp11.h"
#include "InputSystemBase.h"
#include "InputContainer.h"


// be able to map and remap device input at any stage of the Input init !
class SDLInput: private boost::noncopyable {
public:
	static CPP11_CONSTEXPR int GamepadMax = 32768;

	static CPP11_CONSTEXPR int GamepadXBoxA = 0;
	static CPP11_CONSTEXPR int GamepadXBoxB = 1;
	static CPP11_CONSTEXPR int GamepadXBoxC = 2;
	static CPP11_CONSTEXPR int GamepadXBoxD = 3;
	static CPP11_CONSTEXPR int GamepadXBoxStart = 7;

	SDLInput();
	virtual ~SDLInput();
	void updateContainer(InputSystemBase::ContainerArray &, float);

	size_t maxInputDevices() const {
		// one keyboard and 4 gamepads ...
		return 5;
	}

	DeviceList availableInputDevices() const;
	//bool isGamepadAvailable();

private:

	SDL_Event m_event;
	//std::vector<SDL_Joystick *> m_gamepadHandles;
	std::map<int, SDL_Joystick *> m_gamepadHandles;
};
