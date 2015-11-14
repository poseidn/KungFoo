#include "AndroidOpenGLESInterface.h"

#include <array>
#include "../Log.h"

#include "../OpenGLInclude.h"
#include "../Common_OpenGL/GLSupport.h"

#include "../VectorTypes.h"

void AndroidOpenGLESInterface::init(AndroidInitData const& initData, AndroidOpenGLES_State & state) {

	logging::Info() << "Initializing OpenGL on Android with resolution " << initData.getResolution().x() << ":"
			<< initData.getResolution().y();

	const float screenRatio = 16.0 / 9.0;
	// use this for fullscreen
	//const int height = 768;
	const int height = initData.getResolution().y();
	const int width = std::floor(height * screenRatio);

	// enable depth buffer
	GL_CHECK_ERROR(glEnable (GL_DEPTH_TEST));
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

	GL_CHECK_ERROR(glViewport(0, 0, initData.getResolution().x(), initData.getResolution().y()));

	GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));

	GLSupport::setupParallelProjection(initData.getResolution().x(), initData.getResolution().y(), -1.0f,
			1.0f);

	GL_CHECK_ERROR(glMatrixMode(GL_MODELVIEW));
	GL_CHECK_ERROR(glLoadIdentity());

	m_transform = GLSupport::computeScreenTransform(initData.getResolution().x(),
			initData.getResolution().y());
	logging::Info() << "> OpenGL init done";

}

