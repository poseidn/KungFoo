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

#include "Texture.h"

// todo: rename, this does not actually bind, but setup parameters
void Texture::ensureOpenGLBind() {
	if (!m_bound) {
#ifdef USE_ANDROID
		logging::Fatal() << "Texture bound was called on Android-compile code."
				<< "Must not happen because texture binding to context happens on Java-side "
				<< "when loading the texture's image.";
#endif
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
