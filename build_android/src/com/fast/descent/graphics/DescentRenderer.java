package com.fast.descent.graphics;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.util.SparseArray;

import com.fast.descent.DescentLib;
import com.fast.descent.JavaLog;
import com.fast.descent.input.InputContainer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class DescentRenderer implements GLSurfaceView.Renderer {

	private static String TAG = "DescendRenderer";
	private DescentLib m_descentLib;

	private int FpsReportInterval = 0;

	public DescentRenderer(Context context,
			SparseArray<InputContainer> inpCont, DescentLib descentLib) {
		m_lastStartTime = -1;
		m_initialized = false;
		m_inputContainer = inpCont;

		m_descentLib = descentLib;
	}

	// / oh la la:
	// http://stackoverflow.com/questions/10648325/android-smooth-game-loop
	public void onDrawFrame(GL10 gl) {
		if (!m_initialized)
			return;

		m_descentLib.setCurrentGl(gl);

		float deltaT = (float) 0.0;

		if (m_lastStartTime > 0) {
			// convert ns to mili sec

			// deltaT = (float) (((float) (System.currentTimeMillis() -
			// m_lastStartTime)));
			deltaT = (float) (((float) (System.nanoTime() - m_lastStartTime)) * 0.000000001);
		}
		m_lastStartTime = System.nanoTime();

		FpsReportInterval++;
		if (FpsReportInterval > 200) {
			JavaLog.info(TAG, "Current FPS " + 1.0f / deltaT);

			FpsReportInterval = 0;
		}

		//
		/*
		 * gl.glClearColor((float) 0.5f, (float) 0.5f, (float) 0.5f, (float)
		 * 1.0f);
		 */
		// gl.glClear(GL10.GL_DEPTH_BUFFER_BIT | GL10.GL_COLOR_BUFFER_BIT);

		// todo: transfer input container content
		/*
		 * m_descentLib.injectDirectionStickOne(m_inputContainer
		 * .getMovementDirection().x(), m_inputContainer
		 * .getMovementDirection().y());
		 */

		for (int i = 0; i < m_inputContainer.size(); i++) {
			InputContainer contVal = m_inputContainer.valueAt(i);

			//contVal.updateFromOuya();
			contVal.transferInput(m_descentLib);

			contVal.reset();
		}

		m_descentLib.step(deltaT);

	}

	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// TODO: this is probably not so good to do the whole engine setup
		// here ?
		// can this method be called multiple times for one instance ?

		m_descentLib.setCurrentGl(gl);

		Log.i(TAG, "Surface changed to " + width + ":" + height + " - configuring engines");

		// reload textures ?
		if (m_descentLib.isInitialized()) {
			Log.i(TAG, "Game backend already initialized, reloading textures");
			m_descentLib.androidOnResume();
		} else {
			m_descentLib.initEngines(width, height);
			m_descentLib.initGame();
			m_initialized = true;
		}

	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// Do nothing.
	}

	private long m_lastStartTime;
	private SparseArray<InputContainer> m_inputContainer;
	boolean m_initialized;
}