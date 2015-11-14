#pragma once

#include <boost/noncopyable.hpp>
#include "../OpenGLInclude.h"

class LightFactory: boost::noncopyable {
public:
	LightFactory() :
			m_currentLight(GL_LIGHT0) {

	}

	GLenum getNextLight() {
		m_currentLight++;
		return m_currentLight;
	}

	void returnLight(GLenum light) {
		// todo
	}

private:
	int m_currentLight;
};
