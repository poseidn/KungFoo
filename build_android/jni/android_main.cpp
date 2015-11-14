/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code
#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include <DescentEngine/src/JavaInterface.h>

/*

 Important: The JavaInterface must be updated each time a call into the C++ framework happens via
 g_descentFW.setJavaInterface( env, obj );
 because otherwise the references to the Java objects will be old

 */

#include <DescentLogic/src/DescentFramework.h>

#define  LOG_TAG    "libFastDescent"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

AndroidFramework g_descentFW;

extern "C" {
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_initEngines(
		JNIEnv * env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_initGame(JNIEnv * env,
		jobject obj);
JNIEXPORT jboolean JNICALL Java_com_fast_descent_DescentLib_isInitialized(JNIEnv * env,
		jobject obj);
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_androidOnResume(JNIEnv * env,
		jobject obj);
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_step(JNIEnv * env,
		jobject obj, jfloat deltaT);
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_registerTexture(
		JNIEnv * env, jobject obj, jstring name, jint glId, jint frameCount);
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_injectDirectionStickOne(
		JNIEnv * env, jobject obj, jint id, jfloat x, jfloat y);
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_injectKeyDown(
		JNIEnv * env, jobject obj, jint id, jint keyId);
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_registerInputDevice(
		JNIEnv * env, jobject obj, jint devId);
JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_setVirtualControls(
		JNIEnv * env, jobject obj );
JNIEXPORT jfloat JNICALL Java_com_fast_descent_DescentLib_getTileSizeX(
		JNIEnv * env, jobject obj);
JNIEXPORT jfloat JNICALL Java_com_fast_descent_DescentLib_getTileSizeY(
		JNIEnv * env, jobject obj);
}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_initEngines(
		JNIEnv * env, jobject obj, jint width, jint height) {
	LOGI("setupGraphics(%d, %d)", width, height);
	AndroidInitData initData(Vector2(width, height));
	LOGI("initializing render engine");
	g_descentFW.setJavaInterface(env, obj);
	g_descentFW.initRenderEngine(initData);
}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_initGame(JNIEnv * env,
		jobject obj) {
	g_descentFW.setJavaInterface(env, obj);
	g_descentFW.executeBase();
}

JNIEXPORT jboolean JNICALL Java_com_fast_descent_DescentLib_isInitialized(JNIEnv * env,
		jobject obj) {
	g_descentFW.setJavaInterface(env, obj);
	return g_descentFW.isInitialized();
}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_androidOnResume(JNIEnv * env,
		jobject obj) {
	g_descentFW.setJavaInterface(env, obj);
	return g_descentFW.androidOnResume() ;
}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_step(JNIEnv * env,
		jobject obj, jfloat deltaT) {
	g_descentFW.setJavaInterface(env, obj);
	g_descentFW.step(deltaT);
}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_registerTexture(
		JNIEnv * env, jobject obj, jstring name, jint glId, jint frameCount) {
	LOGI("Registering Texture");
	g_descentFW.setJavaInterface(env, obj);
	const char *nativeString = env->GetStringUTFChars(name, NULL);
	std::string cppName(nativeString);
	g_descentFW.getResourceEngine().preloadImage(cppName, (GLuint) glId,
			(int) frameCount);

	env->ReleaseStringUTFChars(name, nativeString);
	LOGI("... done");

}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_injectDirectionStickOne(
		JNIEnv * env, jobject obj, jint id, jfloat x, jfloat y) {
	g_descentFW.setJavaInterface(env, obj);
	g_descentFW.getInputSystem().injectDirectionStickOne(id, Vector2(x, y));
}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_injectKeyDown(
		JNIEnv * env, jobject obj, jint id, jint keyId) {
	g_descentFW.setJavaInterface(env, obj);
	g_descentFW.getInputSystem().injectKeyDown(id, keyId);
}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_registerInputDevice(
		JNIEnv * env, jobject obj, jint devId) {
	g_descentFW.setJavaInterface(env, obj);
	g_descentFW.getInputSystem().registerInputDevice(devId);
}

JNIEXPORT void JNICALL Java_com_fast_descent_DescentLib_setVirtualControls(
		JNIEnv * env, jobject obj ) {
	g_descentFW.setJavaInterface(env, obj);
	g_descentFW.setVirtualControls();
}

JNIEXPORT jfloat JNICALL Java_com_fast_descent_DescentLib_getTileSizeX(
		JNIEnv * env, jobject obj) {
	g_descentFW.setJavaInterface(env, obj);
	return g_descentFW.getRenderEngine().getScreenTransform().getTileSize().x();
}

JNIEXPORT jfloat JNICALL Java_com_fast_descent_DescentLib_getTileSizeY(
		JNIEnv * env, jobject obj) {
	g_descentFW.setJavaInterface(env, obj);
	return g_descentFW.getRenderEngine().getScreenTransform().getTileSize().y();
}

