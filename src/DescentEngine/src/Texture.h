#pragma once

#include <memory>
#include <string>
#include <boost/noncopyable.hpp>

#include "OpenGLInclude.h"

#include "Common_OpenGL/GLSupport.h"

#include "Log.h"

#define DESCENT_TEXTURE_NAME_DEBUG 1

class Texture: public boost::noncopyable {
public:
	// unbound texture, will be done here
	Texture(unsigned int height, unsigned int width, GLint numberOfColors, GLenum textureFormat,
			void * pixelPointer, unsigned int animFrames = 1) :
			m_animationFrames(animFrames), m_height(height), m_width(width), m_numberOfColors(numberOfColors), m_textureFormat(
					textureFormat), m_pixelPointer(pixelPointer), m_bound(false) {

	}

	// already bound textures
	Texture(GLuint id, size_t frameCount = 1) :
			m_animationFrames(frameCount), m_height(0), m_width(0), m_numberOfColors(0), m_textureFormat(0), m_pixelPointer(
					nullptr), m_glId(id), m_bound(true) {

	}

	~Texture() {
		// don't release the OpenGL resources here, on purpose
	}

	GLuint getID() const {
		return m_glId;
	}

	void setID(GLuint id) {
		m_glId = id;
	}

	void setPixelPointer(void * pxPointer) {
		m_pixelPointer = pxPointer;
	}

	void * getPixelPointer() const {
		return m_pixelPointer;
	}

	bool isAnimated() const {
		return (m_animationFrames > 1);
	}

	bool isBound() const {
		return m_bound;
	}

	unsigned int getAnimationFrames() const {
		return m_animationFrames;
	}

	// this has to be done here because we have to ensure, that
	// all OpenGl calls happen on the Render Thread
	void ensureOpenGLBind();

#ifdef DESCENT_TEXTURE_NAME_DEBUG
	void setTextureName(std::string const& name) {
		m_textureName = name;
	}

	std::string const& getTextureName() const {
		return m_textureName;
	}
#endif

#ifdef USE_SDL
	SDL_Surface* m_sdlSurface;
#endif

private:
#ifdef DESCENT_TEXTURE_NAME_DEBUG
	std::string m_textureName;
#endif

	unsigned int m_animationFrames;
	unsigned int m_height;
	unsigned int m_width;
	GLint m_numberOfColors;
	GLenum m_textureFormat;
	void * m_pixelPointer;

	GLuint m_glId;
	bool m_bound;

};
