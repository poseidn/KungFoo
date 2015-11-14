#pragma once

#include <boost/noncopyable.hpp>

//#include <android_native_app_glue.h>
#include "../InterfaceInitData.h"

#include "../Visuals/ScreenTransform.h"

#include "AndroidOpenGLES_State.h"

class android_app {
};

class AndroidInitData: public InterfaceInitData {

public:
	AndroidInitData() = default;

	AndroidInitData(Vector2 const& res) :
			m_res(res) {

	}

	Vector2 const& getResolution() const {
		return m_res;
	}

private:
	Vector2 m_res;
};

class AndroidOpenGLESInterface {
public:
	typedef AndroidInitData InterfaceDataType;

	void init(AndroidInitData const& theApp, AndroidOpenGLES_State & state);

	ScreenTransform const& getScreenTransform() const {
		return m_transform;
	}

private:

	ScreenTransform m_transform;
};
