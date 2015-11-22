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
