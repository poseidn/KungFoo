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

	SDLInterfaceInitData(Vector2Uint reso, bool fscreen = false) :
			Resolution(reso), Fullscreen(fscreen) {
	}

	util::ValidValue<Vector2Uint> Resolution;

	bool Fullscreen;
};

class SDLOpenGLInterface {
public:

	typedef SDLInterfaceInitData InterfaceDataType;

	void init(SDLInterfaceInitData const& data, SDLOpenGL_State & state);

	void Release();

	ScreenTransform const& getScreenTransform() const {
		return m_transform;
	}

private:

	ScreenTransform m_transform;
};
