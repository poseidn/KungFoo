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

#include "../OpenGLInclude.h"
#include "../Util.h"

#include "../Visuals/ScreenTransform.h"
#include "../VectorTypes.h"

#include "../InterfaceInitData.h"
#include "SDLOpenGL_State.h"

class SDLInterfaceInitData: public InterfaceInitData {
public:

	SDLInterfaceInitData() : Fullscreen(false) {
	}

	SDLInterfaceInitData(Vector2UInt reso, bool fscreen = false) :
			Resolution(reso), Fullscreen(fscreen) {
	}

	util::ValidValue<Vector2UInt> Resolution;

	bool Fullscreen;
};

class SDLOpenGLInterface {
public:

	typedef SDLInterfaceInitData InterfaceDataType;

	void init(SDLInterfaceInitData const& data, SDLOpenGL_State & state);

	void release(SDLOpenGL_State & state);

	ScreenTransform const& getScreenTransform() const {
		return m_transform;
	}

private:

	ScreenTransform m_transform;
};
