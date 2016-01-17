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

#include "RenderEngine.h"

#include "Visuals/SpriteVisual.h"

// necessary for picky compilers who don't do ptr_vector destructors when the type is not known...
#ifdef USE_ANDROID_OPENGL

template<>
RenderEngineAbstract<AndroidOpenGLESInterface, OpenGL_ES_Render, AndroidOpenGLES_State>::RenderEngineAbstract()
{

}

template<>
RenderEngineAbstract<AndroidOpenGLESInterface, OpenGL_ES_Render,AndroidOpenGLES_State>::~RenderEngineAbstract()
{
	clearSpriteList();
}

#else

template<>
RenderEngineAbstract<SDLOpenGLInterface, OpenGL_ES_Render, SDLOpenGL_State>::RenderEngineAbstract() {

}

template<>
RenderEngineAbstract<SDLOpenGLInterface, OpenGL_ES_Render, SDLOpenGL_State>::~RenderEngineAbstract() {
	clearSpriteList();
}

#endif

