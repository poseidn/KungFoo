#pragma once

#include <array>

#include "../Log.h"
#include "../OpenGLInclude.h"
#include "../Visuals/ScreenTransform.h"

// define GL_CHECK_ERROR_ENABLED in build system to build
// with GL error check while debugging openGL problems
#define GL_CHECK_ERROR_ENABLED 0
#ifdef GL_CHECK_ERROR_ENABLED
#define GL_CHECK_ERROR( CALL ) {  CALL; GLSupport::checkGlError( #CALL ); }
#else
#define GL_CHECK_ERROR( CALL ) {  CALL; }
#endif

namespace GLSupport {

typedef std::array<GLfloat, 16> Matrix4;

inline ScreenTransform computeScreenTransform(int width, int height) {
	const float screenRatio = float(width) / float(height);
	const float screenRatioWide = 16.0f / 9.0f;
	const float ratioToWide = screenRatio / screenRatioWide;

	// make it smaller if this is not wide
	const float pixelPerTile = (float(height) / 12.0f) * ratioToWide;

	ScreenTransform trans(Vector2(pixelPerTile, pixelPerTile), Vector2(width, height));
	// to have the walls - more or less - centered in the middle of the screen
	trans.setOffset(Vector2(float(width) * 0.155f, 0.0f));

	return trans;
}

inline void checkGlError(std::string const& previousCall) {
	for (GLint error = glGetError(); error; error = glGetError()) {
		logging::Fatal() << "glError: after " << previousCall << ": " << error;
	}
}

inline Matrix4 getParallelProjection(const float resx, const float resy, const float nearPlane,
		const float farPlane) {

// fake glOrtho, taken from http://www.khronos.org/opengles/sdk/1.1/docs/man/glOrtho.xml
	Matrix4 paralleProj = { { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f } };

	paralleProj[0] = 2.0f / (resx);
	paralleProj[5] = 2.0f / (-resy);
	paralleProj[10] = -2.0f / (farPlane - nearPlane); // -2.0f / ( far - near )

	const float tx = -(resx / resx);
	const float ty = -(resy / -resy);
	const float tz = -((farPlane + (nearPlane)) / ((farPlane) - (nearPlane)));

	paralleProj[12] = tx;
	paralleProj[13] = ty;
	paralleProj[14] = tz;
	paralleProj[15] = 1.0f;

	return paralleProj;
}

// implements glOrtho according to
// http://www.khronos.org/opengles/sdk/1.1/docs/man/glOrtho.xml
inline void setupParallelProjection(const float resx, const float resy, const float nearPlane,
		const float farPlane) {
	GL_CHECK_ERROR(glMatrixMode (GL_PROJECTION));
	GL_CHECK_ERROR(glLoadIdentity());

// fake glOrtho, taken from http://www.khronos.org/opengles/sdk/1.1/docs/man/glOrtho.xml
	Matrix4 paralleProj = getParallelProjection(resx, resy, nearPlane, farPlane);
	GL_CHECK_ERROR(glMultMatrixf(&paralleProj.front()));
}

}
