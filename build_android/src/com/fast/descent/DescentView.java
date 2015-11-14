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

package com.fast.descent;

/*
 * Copyright (C) 2008 The Android Open Source Project
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

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.util.SparseArray;
import android.view.MotionEvent;

import com.fast.descent.graphics.ConfigChooser;
import com.fast.descent.graphics.DescentRenderer;
import com.fast.descent.input.InputContainer;
import com.fast.descent.input.Vector2;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

/**
 * A simple GLSurfaceView sub-class that demonstrate how to perform OpenGL ES
 * 2.0 rendering into a GL Surface. Note the following important details:
 * 
 * - The class must use a custom context factory to enable 2.0 rendering. See
 * ContextFactory class definition below.
 * 
 * - The class must use a custom EGLConfigChooser to be able to select an
 * EGLConfig that supports 2.0. This is done by providing a config specification
 * to eglChooseConfig() that has the attribute EGL10.ELG_RENDERABLE_TYPE
 * containing the EGL_OPENGL_ES2_BIT flag set. See ConfigChooser class
 * definition below.
 * 
 * - The class must select the surface's format, then choose an EGLConfig that
 * matches it exactly (with regards to red/green/blue/alpha channels bit
 * depths). Failure to do so would result in an EGL_BAD_MATCH error.
 */
class DescentView extends GLSurfaceView {
	private static String TAG = "DescentView";
	private static final boolean DEBUG = false;

	private float padCenterX = 0.0f;
	private float padCenterY = 0.0f;
	private final float maxPadDistance = 0.2f;
	private final float sensitivePadDistance = 0.3f;

	private float button1CenterX = 0.0f;
	private float button1CenterY = 0.0f;
	private float button2CenterX = 0.0f;
	private float button2CenterY = 0.0f;

	private float buttonDividerX = 0.0f;
	private float buttonDividerY = 0.0f;

	private float buttonLimitX = 0.0f;

	private float padLimitsX = 0.0f;
	private float padLimitsY = 0.0f;

	private boolean padPositionsSet = false;

	// id of the finger which touched first on the
	// side of the dpad
	private boolean PadFingerSet = false;
	private int PadFingerId = -1;

	/*
	 * public DescentView(Context context, DescentRenderer renderer) {
	 * 
	 * super(context);
	 * 
	 * m_inputContainer = inpContainer; m_soundBackend = soundbk;
	 * 
	 * initTextureList(); init(false, 16, 0, renderer); }
	 */

	// used by tools
	public DescentView(Context context) {
		super(context);
	}

	public DescentView(Context context, boolean translucent, int depth,
			int stencil, DescentRenderer renderer, DescentLib lib,
			SparseArray<InputContainer> inputs) {
		super(context);

		m_inputContainer = inputs;
		m_lib = lib;

		init(translucent, depth, stencil);

		/* Set the renderer responsible for frame rendering */
		setRenderer(renderer);
	}

	// this takes events from ACTION_DOWN and ACTION_POINTER_DOWN
	// which are treated differently by android but is for us only
	// differing on the location which has been touched
	private boolean handleGenericDown(MotionEvent event) {
		// todo: multitouch does not work
		// todo: the button positions are not correct

		if (!padPositionsSet) {

			// button & pad configuration
			final float padTilePosX = (float) 3.0;
			final float padTilePosY = (float) 3.0;

			final float button1TilePosX = (float) 3.0;
			final float button1TilePosY = (float) 6.5;

			final float button2TilePosX = (float) 3.0;
			final float button2TilePosY = (float) 2.0;

			// in pixel
			final float tileSizeX = m_lib.getTileSizeX();
			final float tileSizeY = m_lib.getTileSizeY();

			// tile size in the relative cooords [0,1]
			float tileRelX = tileSizeX / (float) getWidth();
			float tileRelY = tileSizeY / (float) getHeight();

			// the amount of tiles, which fit on the screen
			// final float sizeInTilesX = (float) getWidth() / tileSizeX;
			// final float sizeInTilesY = (float) getHeight() / tileSizeY;

			/*
			 * Vector2 posDpad(3.0f, 3.0f); Vector2 posButton1(sizeTiles.x() -
			 * 3.0f, 6.5f); Vector2 posButton2(sizeTiles.x() - 3.0f, 2.0f);
			 */

			padCenterX = (float) (tileRelX * padTilePosX);
			// the coords start from the top
			padCenterY = (float) (1.0 - tileRelY * padTilePosY);

			button1CenterX = (float) (1.0 - tileRelX * button1TilePosX);
			button1CenterY = (float) (1.0 - tileRelY * button1TilePosY);

			button2CenterX = (float) (1.0 - tileRelX * button2TilePosX);
			button2CenterY = (float) (1.0 - tileRelY * button2TilePosY);

			buttonDividerY = (float) (1.0 - tileRelY
					* (button1TilePosY + button2TilePosY) * 0.5);

			buttonLimitX = (float) (1.0 - tileRelX * button2TilePosX * 2.0);

			padLimitsX = (float) (tileRelX * padTilePosX * 2.0);
			padLimitsY = (float) (1.0 - tileRelY * padTilePosY * 2.0);
			// todo: do left handed people need d-pad and
			// button switched

			// this should also work on touch screen, where
			// the two buttons only take up a small part on the
			// lower right part of the screen

			Log.i(TAG, "Computed Control pad center to " + padCenterX + ":"
					+ padCenterY);
			Log.i(TAG, "Computed Button1 center to " + button1CenterX + ":"
					+ button1CenterY);
			Log.i(TAG, "Computed Button2 pad center to " + button2CenterX + ":"
					+ button2CenterY);

			padPositionsSet = true;
		}

		// get the position of the this touch point
		int index = event.getActionIndex();
		final float relX = event.getX(index) / (float) getWidth();
		final float relY = event.getY(index) / (float) getHeight();
		// first pressed gesture has started

		Log.i(TAG, "Touch at" + relX + ":" + relY);

		InputContainer ipC = m_inputContainer.get(0);

		// check if this was a click on an action surface
		if (relX > buttonLimitX) {

			// check w
			if (relY < buttonDividerY) {
				/*
				 * ipC.setKeyDownMenu(true); } else if ((relY > buttonEndMenu)
				 * && (relY < buttonEndJump)) {
				 */
				ipC.setKeyDownJump(true);
			} else {
				ipC.setKeyDownKick(true);
			}
		}

		if ((relX < padLimitsX) && (relY > padLimitsY)) {
			// touch on our virtual analog pad ... ?
			int id = event.getPointerId(index);

			PadFingerSet = true;
			PadFingerId = id;

			handleMoveStick(event);

		}

		return true;
	}

	private void handleGenericUp(MotionEvent event) {

		// is this the trigger finger, which has been unset ?
		if (PadFingerSet) {

			int index = event.getActionIndex();
			int id = event.getPointerId(index);

			int pointerIndex = event.findPointerIndex(PadFingerId);
			if (pointerIndex < 0) {
				Log.e(TAG, "Point index for id " + PadFingerId + " not found");
				return;
			}

			if (PadFingerId == id) {
				// reset all movements
				InputContainer ipC = m_inputContainer.get(0);
				ipC.setMovementDirection(Vector2.Unit());
				PadFingerSet = false;
			}
		}

	}

	private void handleMoveStick(MotionEvent event) {

		// nothing to do for us here
		if ( ! PadFingerSet)
			return;

		int pointerIndex = event.findPointerIndex(PadFingerId);
		if (pointerIndex < 0) {
			Log.e(TAG, "Point index for id " + PadFingerId + " not found");
			return;
		}

		final float relX = event.getX(pointerIndex) / (float) getWidth();
		final float relY = event.getY(pointerIndex) / (float) getHeight();

		float dist = (float) Math.sqrt(Math.pow(relX - padCenterX, 2.0f)
				+ (float) Math.pow(relY - padCenterY, 2.0f));

		InputContainer ipC = m_inputContainer.get(0);

		if (dist < sensitivePadDistance) {
			// Math.min( maxPadDistance, dist );
			final float diffX = relX - padCenterX;
			final float diffY = relY - padCenterY;

			final float relDiffX = diffX / maxPadDistance;
			final float relDiffY = diffY / maxPadDistance;

			// JavaLog.info("DescentView", "MOVE relDiff " + relDiffX + ":"
			// + relDiffY);

			ipC.setMovementDirection(new Vector2(relDiffX
					* InputContainer.StickOneMax, -relDiffY
					* InputContainer.StickOneMax));
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {

		final int action = event.getAction();
		/*
		 * Switch on the action. The action is extracted from the event by
		 * applying the MotionEvent.ACTION_MASK. Alternatively a call to
		 * event.getActionMasked() would yield in the action as well.
		 */
		switch (action & MotionEvent.ACTION_MASK) {
		case MotionEvent.ACTION_DOWN: {
			// Log.i(TAG, "MotionEvent.ACTION_DOWN");
			handleGenericDown(event);
			break;
		}

		case MotionEvent.ACTION_POINTER_DOWN: {
			// Log.i(TAG, "MotionEvent.ACTION_POINTER_DOWN");

			handleGenericDown(event);
			break;
		}

		case MotionEvent.ACTION_UP: {
			/*
			 * Final pointer has gone up and has ended the last pressed gesture.
			 */

			handleGenericUp(event);
			break;
		}

		case MotionEvent.ACTION_POINTER_UP: {
			/*
			 * A non-primary pointer has gone up and other pointers are still
			 * active.
			 */

			handleGenericUp(event);
			break;
		}

		case MotionEvent.ACTION_MOVE: {
			/*
			 * A change event happened during a pressed gesture. (Between
			 * ACTION_DOWN and ACTION_UP or ACTION_POINTER_DOWN and
			 * ACTION_POINTER_UP)
			 */

			/*
			 * Loop through all active pointers contained within this event.
			 * Data for each pointer is stored in a MotionEvent at an index
			 * (starting from 0 up to the number of active pointers). This loop
			 * goes through each of these active pointers, extracts its data
			 * (position and pressure) and updates its stored data. A pointer is
			 * identified by its pointer number which stays constant across
			 * touch events as long as it remains active. This identifier is
			 * used to keep track of a pointer across events.
			 */
			for (int index = 0; index < event.getPointerCount(); index++) {
				// get pointer id for data stored at this index
				int id = event.getPointerId(index);
			}
			// Log.i(TAG, "MotionEvent.ACTION_MOVE");
			handleMoveStick(event);

			break;
		}

		}
		return true;
	};

	private void init(boolean translucent, int depth, int stencil) {

		/*
		 * By default, GLSurfaceView() creates a RGB_565 opaque surface. If we
		 * want a translucent one, we should change the surface's format here,
		 * using PixelFormat.TRANSLUCENT for GL Surfaces is interpreted as any
		 * 32-bit surface with alpha by SurfaceFlinger.
		 */
		if (translucent) {
			this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
		}

		/*
		 * Setup the context factory for 2.0 rendering. See ContextFactory class
		 * definition below
		 */
		setEGLContextFactory(new ContextFactory());

		/*
		 * We need to choose an EGLConfig that matches the format of our surface
		 * exactly. This is going to be done in our custom config chooser. See
		 * ConfigChooser class definition below.
		 */
		setEGLConfigChooser(translucent ? new ConfigChooser(8, 8, 8, 8, depth,
				stencil, DEBUG) : new ConfigChooser(5, 6, 5, 0, depth, stencil,
				DEBUG));

	}

	private static class ContextFactory implements
			GLSurfaceView.EGLContextFactory {
		private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

		public EGLContext createContext(EGL10 egl, EGLDisplay display,
				EGLConfig eglConfig) {
			Log.w(TAG, "creating OpenGL ES 1.0 context");
			checkEglError("Before eglCreateContext", egl);

			// create OpenGL es 1 context
			// use "2" to create an OpenGL ES 2 context
			int[] attrib_list = { EGL_CONTEXT_CLIENT_VERSION, 1, EGL10.EGL_NONE };
			EGLContext context = egl.eglCreateContext(display, eglConfig,
					EGL10.EGL_NO_CONTEXT, attrib_list);
			checkEglError("After eglCreateContext", egl);
			return context;
		}

		public void destroyContext(EGL10 egl, EGLDisplay display,
				EGLContext context) {
			egl.eglDestroyContext(display, context);
		}
	}

	private static void checkEglError(String prompt, EGL10 egl) {
		int error;
		while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
			Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
		}
	}

	private SparseArray<InputContainer> m_inputContainer;
	private DescentLib m_lib;

}
