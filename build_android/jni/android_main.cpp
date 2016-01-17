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
#include <android_native_app_glue.h>
#include <android/native_window_jni.h>
//#include <JNIHelper.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <atomic>
#include <chrono>
namespace chr = std::chrono;

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

struct user_data {
	user_data() {
		is_ready = false;
		has_focus = false;
		after_resume = false;
	}

	std::unique_ptr<AndroidFramework> framework;
	std::atomic<bool> is_ready;
	std::atomic<bool> has_focus;
	std::atomic<bool> after_resume;

};

static int32_t engine_handle_input(struct android_app* app,
		AInputEvent* event) {
	//struct engine* engine = (struct engine*)app->userData;
	auto udata = (user_data*) app->userData;

	auto etype = AInputEvent_getType(event);
	if (etype == AINPUT_EVENT_TYPE_MOTION) {
		int32_t atype = AMotionEvent_getAction(event);
		uint32_t action = atype & AMOTION_EVENT_ACTION_MASK;

		int32_t finger_index = (atype & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
				>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
		int32_t finger_id = AMotionEvent_getPointerId(event, finger_index);

		float pointer_x = AMotionEvent_getX(event, finger_index);
		float pointer_y = AMotionEvent_getY(event, finger_index);

		/*LOGI(
		 "got motion event with (%f,%f) and id %i and index %i raw action %i",
		 x, y, finger_id, finger_index, action);*/

		// we accpet both the primary or secondary pointer
		if ((action == AMOTION_EVENT_ACTION_DOWN)
				|| (action == AMOTION_EVENT_ACTION_POINTER_DOWN)) {
			//LOGI("AMOTION_EVENT_ACTION_DOWN");
			udata->framework->getInputSystem()->injectTouchDown(finger_id,
					pointer_x, pointer_y);
		} else if (action == AMOTION_EVENT_ACTION_MOVE) {
			LOGI("AMOTION_EVENT_ACTION_MOVE");

			// always extract all finger position, because if there is more
			// than one finger on the touch screen, in case of AMOTION_EVENT_ACTION_MOVE
			// the finger_index will always be the index of the pointer finger (first finger
			// which touched down) and not of the finger which actually moved

			size_t pointerCount = AMotionEvent_getPointerCount(event);

			AndroidInput::FingerLocationList locList;
			for (size_t iPointer = 0; iPointer < pointerCount; iPointer++) {
				float x = AMotionEvent_getX(event, iPointer);
				float y = AMotionEvent_getY(event, iPointer);
				int32_t id = AMotionEvent_getPointerId(event, iPointer);
				locList.push_back(AndroidInput::FingerLocation(id, x, y));
			}

			udata->framework->getInputSystem()->injectTouchMove(locList);
		} else if ((action == AMOTION_EVENT_ACTION_UP)
				|| (action == AMOTION_EVENT_ACTION_POINTER_UP)) {
			//LOGI("AMOTION_EVENT_ACTION_UP");
			udata->framework->getInputSystem()->injectTouchUp(finger_id);
		}

		return 1;
	}
	return 0;
}

static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
	// todo: extract custom engine data ....
	auto udata = (user_data*) app->userData;

	switch (cmd) {
	case APP_CMD_START:
		LOGI("APP_CMD_START");

		// create game framework
		udata->framework.reset(new AndroidFramework());
		// allows framework internal classes to perform calls into the Activities
		// java code
		udata->framework->setJavaInterface(app->activity);

		// transfer some important services
		udata->framework->setAssetManager(app->activity->assetManager);

		// inializes framework components
		udata->framework->execute();

		break;
	case APP_CMD_INIT_WINDOW: {
		LOGI("APP_CMD_INIT_WINDOW");

		// maybe made optional, if some gamepads are registered with android
		udata->framework->setVirtualControls();

		// setup OpenGL ES and start loading graphics
		AndroidInitData initData(app);
		udata->framework->initRenderEngine(initData);
		udata->is_ready.store(true);
	}
		break;

	case APP_CMD_PAUSE:
		LOGI("APP_CMD_PAUSE");
		udata->after_resume.store(false);
		break;
	case APP_CMD_RESUME:
		LOGI("APP_CMD_RESUME");
		udata->after_resume.store(true);
		break;

	case APP_CMD_GAINED_FOCUS:
		LOGI("APP_CMD_GAINED_FOCUS");
		udata->has_focus.store(true);
		udata->framework->resumeGame();
		break;

	case APP_CMD_LOST_FOCUS:
		LOGI("APP_CMD_LOST_FOCUS");
		udata->has_focus.store(false);
		udata->framework->pauseGame();
		break;

	case APP_CMD_TERM_WINDOW:
		LOGI("APP_CMD_TERM_WINDOW");

		udata->is_ready.store(false);

		// free all Open GL resources, once this has the called,
		// the surface cannot be re-used
		udata->framework->freeAllTextures();
		udata->framework->releaseRenderEngine();

		break;
	case APP_CMD_STOP:
		LOGI("APP_CMD_STOP");

		udata->is_ready.store(false);

		// destroy all game state
		// game will start from scratch next time
		udata->framework.release();

		break;
	case APP_CMD_DESTROY:
		// free all loaded game resources
		LOGI("APP_CMD_DESTROY");
		break;
	}
}

void android_main(android_app* and_app) {
	app_dummy();

	user_data udata;

	/*
	 g_engine.SetState( state );

	 //Init helper functions
	 ndk_helper::JNIHelper::Init( state->activity, HELPER_CLASS_NAME );
	 */
	// todo: will be our engine data later on
	and_app->userData = &udata;
	and_app->onAppCmd = engine_handle_cmd;
	and_app->onInputEvent = engine_handle_input;

#ifdef USE_NDK_PROFILER
	monstartup("libTeapotNativeActivity.so");
#endif

	LOGI("android_main started");
	// loop waiting for stuff to do.

	chr::high_resolution_clock::time_point lastStart;
	while (1) {
		std::chrono::milliseconds msecs = chr::duration_cast
				< std::chrono::milliseconds
				> (chr::high_resolution_clock::now() - lastStart);
		auto delta_seconds = msecs.count() * 0.001f;
		lastStart = chr::high_resolution_clock::now();

		if (delta_seconds > 10.0f) {
			// too big, treat as very short
			delta_seconds = 0.000001f;
		}

		// Read all pending events.
		int id;
		int events;
		android_poll_source* source;

		bool engineReady = udata.is_ready.load();
		const bool is_interactive = udata.has_focus.load()
				&& udata.after_resume.load();
		//LOGI( "%i", engineReady && is_interactive);

		const bool is_animating = engineReady && is_interactive;

		//and_app->isRenderEngineReady;

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((id = ALooper_pollAll(
				(udata.has_focus.load() && udata.after_resume.load()
						&& udata.is_ready.load()) ? 0 : -1, NULL, &events,
				(void**) &source)) >= 0) {
			// Process this event.
			if (source != NULL)
				source->process(and_app, source);

			//g_engine.ProcessSensors( id );

			// Check if we are exiting.
			if (and_app->destroyRequested != 0) {
				//g_engine.TermDisplay();
				return;
			}
		}

		if (engineReady && is_interactive) {
			// Drawing is throttled to the screen update rate, so there
			// is no need to do timing here.
			// todo: correct time step
			udata.framework->step(delta_seconds);
		}
	}
}
