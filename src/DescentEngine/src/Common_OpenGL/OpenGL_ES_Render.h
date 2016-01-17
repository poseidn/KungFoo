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

#include "../VectorTypes.h"
#include "../Visuals/SpriteVisualList.h"
#include "../Visuals/ParticleSystemVisualList.h"
#include "../Visuals/TextVisualList.h"

#include "../OpenGLInclude.h"

#ifdef USE_ANDROID_OPENGL
#include "../Android_OpenGL/AndroidOpenGLES_State.h"
#else
#include "../SDL_OpenGL/SDLOpenGL_State.h"

#endif

#include "GLSupport.h"

class ScreenTransform;

// todo: move to using http://www.songho.ca/opengl/gl_vbo.html
// it is faster then vertex arrays
class OpenGL_ES_Render: boost::noncopyable {
public:

	OpenGL_ES_Render() {
		// initialiaze the render matrix, this is just temporary and will be overwritten by
		// the corerct values
		m_defaultProjection = GLSupport::getParallelProjection(640.0, 480.0, 1.0f, 1.0f);
	}

#ifdef USE_ANDROID_OPENGL
	typedef AndroidOpenGLES_State RenderState;
#else
	typedef SDLOpenGL_State RenderState;
#endif

	void renderBegin();

	void renderSpriteVisual(SpriteVisualSVector & ent, bool ingameSprite, float deltaT);

	void renderParticleSystemVisual(ParticeSystemVisualListUniq const& part);

	// ingameText are text visuals which are provided in game coordinates
	// rather than screen coordinates
	void renderTextVisual(TextVisualListUniq const& part, bool ingameText);

	void renderEnd(RenderState & state);

	void renderSetupCam();

	void resetTranslation(ScreenTransform const& st);

	// the tile at this coordinate will be displayed at the bottom left of the screen
	void setCameraLocation(ScreenTransform const& st, Vector3 const& vec, bool useOffsetX = true, bool useOffsetY =
			false);

	Vector3 getCameraLocation(ScreenTransform const& st) const;

	void setDebugFaces(bool b) {
		m_debugFaces = b;
	}

	bool getDebugFaces() const {
		return m_debugFaces;
	}

private:

	Vector3 getZeroCameraLocation(ScreenTransform const& st) const;

	Vector3 getCameraLocationDetail(ScreenTransform const& st, Vector3 const& translate) const;

	Vector3 m_camTranslate;
	GLSupport::Matrix4 m_defaultProjection;
	bool m_debugFaces = false;
};
