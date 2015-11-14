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

