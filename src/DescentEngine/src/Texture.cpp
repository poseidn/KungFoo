#include "Texture.h"

void Texture::ensureOpenGLBind() {
	if (!m_bound) {
		// only executed for x86 build
		// for the Android platform, the textures are bound on the java side

		logging::Info() << "Binding texture " << getTextureName() << " to OpenGL";
		GL_CHECK_ERROR(glGenTextures(1, &m_glId));

		// Bind the texture object
		GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, m_glId));

		// Set the texture's stretching properties
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// this will not use any kind of filtering to blur / anti-alise the textures
		// setting when the texture is farther away than it's original size
		GL_CHECK_ERROR (glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		// setting when the textre is closer than it's original size
		GL_CHECK_ERROR (glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		// Edit the texture object's image data using the information SDL_Surface gives us
		GL_CHECK_ERROR (
				glTexImage2D(GL_TEXTURE_2D, 0, m_numberOfColors, m_width, m_height, 0, m_textureFormat,
						GL_UNSIGNED_BYTE, m_pixelPointer));
		m_bound = true;
	}
}
