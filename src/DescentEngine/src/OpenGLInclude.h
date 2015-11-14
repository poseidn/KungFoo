#pragma once

#ifdef USE_SDL_OPENGL
#include "SDL_include.h"

#elif USE_ANDROID_OPENGL
#include <EGL/egl.h>
#include <GLES/gl.h>

#else
// fallback for Eclipse GUI
#include "SDL_include.h"

#endif
