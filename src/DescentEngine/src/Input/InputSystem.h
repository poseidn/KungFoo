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

#include "../Cpp11.h"

#include "MultiplexedInput.h"
#include "DelayedInput.h"

#ifdef USE_SDL

#include "SDLInput.h"

// todo: refactor this SLDInput to be fixed here
class InputSystem CPP11_FINAL : public MultiplexedInput<SDLInput, DelayedInput>
{
public:
	InputSystem ( SDLInput * iA, DelayedInput * iB ): MultiplexedInput ( iA, iB) {}

};

#endif

#ifdef USE_ANDROID

#include "AndroidInput.h"

class InputSystem CPP11_FINAL : public AndroidInput {

};
#endif
