#include "AndroidOpenGLESInterface.h"

#include <array>
#include "../Log.h"

#include "../OpenGLInclude.h"
#include "../Common_OpenGL/GLSupport.h"

#include "../VectorTypes.h"

void AndroidOpenGLESInterface::init(AndroidInitData const& initData,
		AndroidOpenGLES_State & state) {

	logging::Info() << "Creating OpenGL ES Surface";

	auto android_app = initData.getAndroidApp();
	assert(android_app);

	/*
	 * Here specify the attributes of the desired configuration.
	 * Below, we select an EGLConfig with at least 8 bits per color
	 * component compatible with on-screen windows
	 */
	const EGLint attribs[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_BLUE_SIZE,
			8, EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_NONE };
	EGLint w, h, dummy, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);

	/* Here, the application chooses the configuration it desires. In this
	 * sample, we have a very simplified selection process, where we pick
	 * the first EGLConfig that matches our criteria */
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);

	/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	 * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	 * As soon as we picked a EGLConfig, we can safely reconfigure the
	 * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(android_app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, android_app->window,
			NULL);
	context = eglCreateContext(display, config, NULL, NULL);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		logging::Fatal() << "Unable to eglMakeCurrent";
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	state.display = display;
	state.context = context;
	state.surface = surface;
	state.width = w;
	state.height = h;

	logging::Info() << "Initializing OpenGL on Android with resolution " << w
			<< ":" << h;

	// enable depth buffer
	GL_CHECK_ERROR(glEnable (GL_DEPTH_TEST));
	GL_CHECK_ERROR(glDepthFunc (GL_LEQUAL));
	GL_CHECK_ERROR(glDepthMask (GL_TRUE));

	// Initialize GL state.
	GL_CHECK_ERROR(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST));

	// enable various OpenGl stuff
	GL_CHECK_ERROR(glEnable(GL_TEXTURE_2D));
	GL_CHECK_ERROR(glEnable (GL_BLEND));
	GL_CHECK_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// black background
	//GL_CHECK_ERROR(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	// white background
	GL_CHECK_ERROR(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

	GL_CHECK_ERROR(glViewport(0, 0, w, h));

	GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));

	GLSupport::setupParallelProjection(w, h, -1.0f, 1.0f);

	GL_CHECK_ERROR(glMatrixMode(GL_MODELVIEW));
	GL_CHECK_ERROR(glLoadIdentity());

	m_transform = GLSupport::computeScreenTransform(w, h);
	logging::Info() << "OpenGL init done with width " << w << " and height " << h;
}

void AndroidOpenGLESInterface::release(AndroidOpenGLES_State & state) {
	// note: textures will be unloaded via the ResourceEngine
    if (state.display != EGL_NO_DISPLAY) {
        eglMakeCurrent(state.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (state.context != EGL_NO_CONTEXT) {
            eglDestroyContext(state.display, state.context);
        }
        if (state.surface != EGL_NO_SURFACE) {
            eglDestroySurface(state.display, state.surface);
        }
        eglTerminate(state.display);
    }
    state.display = EGL_NO_DISPLAY;
    state.context = EGL_NO_CONTEXT;
    state.surface = EGL_NO_SURFACE;

	logging::Info() << "OpenLG unloading done";
}

