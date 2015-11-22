#pragma once

#include <boost/noncopyable.hpp>

#include "../OpenGLInclude.h"

class AndroidOpenGLES_State {
public:
	/*EGLDisplay m_display;
	 EGLSurface m_surface;
	 EGLContext m_context;
	 int32_t m_width;
	 int32_t m_height;*/
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display;
	int width;
	int height;
};
