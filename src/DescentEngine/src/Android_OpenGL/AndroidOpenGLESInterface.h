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

#include <android_native_app_glue.h>
#include "../InterfaceInitData.h"

#include "../Visuals/ScreenTransform.h"

#include "AndroidOpenGLES_State.h"

class AndroidInitData: public InterfaceInitData {

public:
	AndroidInitData() = default;

	AndroidInitData(android_app * app) :
			m_android_app (app) {
	}

	android_app * getAndroidApp() const {
		return m_android_app;
	}

private:
	android_app * m_android_app = nullptr;
};

class AndroidOpenGLESInterface {
public:
	typedef AndroidInitData InterfaceDataType;

	void init(AndroidInitData const& theApp, AndroidOpenGLES_State & state);
	void release(AndroidOpenGLES_State & state);

	ScreenTransform const& getScreenTransform() const {
		return m_transform;
	}

private:

	ScreenTransform m_transform;
};
