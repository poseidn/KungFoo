/*
 * Copyright (C) 2007 The Android Open Source Project
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

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.hardware.input.InputManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.util.SparseArray;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;

import com.fast.descent.exceptions.ResourceNotFound;
import com.fast.descent.graphics.DescentRenderer;
import com.fast.descent.input.InputContainer;
import com.fast.descent.input.Vector2;
import com.fast.descent.resources.FileBackend;
import com.fast.descent.sound.SoundBackend;

import java.io.IOException;

// ouyal support disabled atm
//import tv.ouya.console.api.OuyaController;
//import tv.ouya.console.api.OuyaIntent;

class ShutdownBroadcastReceiver extends BroadcastReceiver {
	public ShutdownBroadcastReceiver(SoundBackend sndBackend) {
		m_sndBackend = sndBackend;
	}

	@Override
	public void onReceive(Context context, Intent intent) {
	/*	if (intent.getAction().equals(OuyaIntent.ACTION_MENUAPPEARING)) {
			// will only be called, once the application is left via a
			// double-tap of the
			// menu button
			JavaLog.info("DescentActivity", "ACTION_MENUAPPEARING called");
			m_sndBackend.pauseSound();
		}*/
	}

	SoundBackend m_sndBackend;
}

@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
public class DescentActivity extends Activity {

	DescentView m_view;
	private DescentRenderer m_renderer;
	private DescentLib m_descentLib;

	private boolean ControlEventBased = true;

	static String TAG = "DescentActivity";

	// input container for device ids
	private SparseArray<InputContainer> m_inputContainer;
	private SoundBackend m_soundBackend = new SoundBackend();
	private FileBackend m_fileBackend;

	//private ShutdownBroadcastReceiver m_shutdownReceiver;

	/*
	 * @Override public void onConfigurationChanged(
	 * android.content.res.Configuration newConfig) {
	 * 
	 * super.onConfigurationChanged(newConfig);
	 * 
	 * // newConfig.ori if (newConfig.orientation ==
	 * android.content.res.Configuration.ORIENTATION_LANDSCAPE) { Log.i(TAG,
	 * "ORIENTATION_LANDSCAPE"); } if (newConfig.orientation ==
	 * android.content.res.Configuration.ORIENTATION_PORTRAIT) { Log.i(TAG,
	 * "ORIENTATION_PORTRAIT"); }
	 * 
	 * };
	 */
	@Override
	protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		// setup Ouya Controller
		//OuyaController.init(this);

		// register receiver is case this app is shut down

		
		/*
		 * m_shutdownReceiver = new ShutdownBroadcastReceiver(m_soundBackend);
		 * this.registerReceiver(m_shutdownReceiver, new IntentFilter(
				OuyaIntent.ACTION_MENUAPPEARING));
		*/

		// m_inputContainer = new InputContainer(!ControlEventBased);
		m_inputContainer = new SparseArray<InputContainer>();
		String[] assets;
		try {
			assets = this.getAssets().list("images");
			JavaLog.info("ASSETS", "found " + assets.length + " assets");
			for (int i = 0; i < assets.length; i++) {
				JavaLog.info("ASSETS", assets[i]);
			}
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		// preload Sound backend
		try {
			m_soundBackend.preloadMusic(this, "musik1");
			m_soundBackend.preloadSound(this, "player_jump1");
			m_soundBackend.preloadSound(this, "player_kick1");
			m_soundBackend.preloadSound(this, "player_yell1");
			m_soundBackend.preloadSound(this, "player_yell2");
			m_soundBackend.preloadSound(this, "player_yell3");
			m_soundBackend.preloadSound(this, "dead_siren");

		} catch (ResourceNotFound e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			this.finish();
			return;
		}

		m_fileBackend = new FileBackend((Context) this);

		m_descentLib = new DescentLib(m_soundBackend, m_fileBackend);
		m_renderer = new DescentRenderer((Context) this, m_inputContainer,
				m_descentLib);

		m_view = new DescentView((Context) this, false, 16, 0, m_renderer,
				m_descentLib, m_inputContainer);

		InputManager mInp = (InputManager) getSystemService(Context.INPUT_SERVICE);

		int[] ids = mInp.getInputDeviceIds();
		JavaLog.info(TAG, ids.length + " device ids found");
		for (int i = 0; i < ids.length; i++) {
			InputDevice dev = mInp.getInputDevice(ids[i]);
			JavaLog.info(TAG, "Device " + dev.getName() + " found");
			JavaLog.info(TAG, "Descriptor " + dev.getDescriptor());
			JavaLog.info(TAG, "Id " + dev.getId());

			// gpio-input devices gives 1 with this test
			JavaLog.info(TAG, "Source gamepad "
					+ (dev.getSources() & InputDevice.SOURCE_GAMEPAD));
			// gpio-input devices gives 0 with this test
			JavaLog.info(TAG, "Source joystick "
					+ (dev.getSources() & InputDevice.SOURCE_JOYSTICK));

			boolean isJoystick = (dev.getSources() & InputDevice.SOURCE_JOYSTICK) > 0;

			// seems not to work with the x360 gamepad on linux and qemu..
			// register this input devices with the input system
			if (isJoystick) {
				int thisId = dev.getId();
				JavaLog.info(TAG, "Registering Device " + dev.getName()
						+ " as gamepad with id " + thisId);
				m_descentLib.registerInputDevice(thisId);

				// create the according inputContainer
				m_inputContainer.put(Integer.valueOf(dev.getId()),
						new InputContainer(dev.getId(), !ControlEventBased));

			}

		}

		// ANDROID TOUCH, add the touch device without using the
		// no gamepads found, assume there is just one touch interface
		if (m_inputContainer.size() == 0) {
			JavaLog.info(TAG, "No input container. Setting up touch input ...");

			m_descentLib.registerInputDevice(0);
			// create the according inputContainer
			m_inputContainer.put(0, new InputContainer(0, false));
			m_descentLib.setVirtualControls();

			JavaLog.info(TAG, "Android touch setup done");
		}

		setContentView(m_view);
	}

	@Override
	public boolean onGenericMotionEvent(MotionEvent event) {
		if (!ControlEventBased)
			return false;

		if ((event.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) == 0) {
			// Not a joystick movement, so ignore it.
			return false;
		}

		int odid = event.getDeviceId();
		InputContainer matchingCont = m_inputContainer.get(Integer
				.valueOf(odid));
		if (matchingCont == null)
			// device has not been mapped
			return false;

		// 1.0f is the max !
	/*	float movX = event.getAxisValue(OuyaController.AXIS_LS_X);
		if (Math.abs(movX) < OuyaController.STICK_DEADZONE)
			movX = 0.0f;
		float movY = event.getAxisValue(OuyaController.AXIS_LS_Y);
		if (Math.abs(movY) < OuyaController.STICK_DEADZONE)
			movY = 0.0f;
		matchingCont.setMovementDirection(new Vector2(movX
				* InputContainer.StickOneMax, -movY
				* InputContainer.StickOneMax));
*/

		return true;
	}

	// must be here and not in the view in order to work !
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		/*
		 * switch (keyCode) { case KeyEvent.KEYCODE_B: Log.e(TAG, "b pressed");
		 * MediaPlayer mediaPlayer = MediaPlayer.create(this, R.raw.musik1);
		 * mediaPlayer.start(); // no need to call prepare(); create() does //
		 * that for you break; case KeyEvent.KEYCODE_DPAD_UP: Log.e(TAG,
		 * "up pressed"); m_inputContainer.getMovementDirection().setY(
		 * InputContainer.StickOneMax); break; case KeyEvent.KEYCODE_DPAD_DOWN:
		 * m_inputContainer.getMovementDirection().setY(
		 * -InputContainer.StickOneMax); break; case KeyEvent.KEYCODE_DPAD_LEFT:
		 * m_inputContainer.getMovementDirection().setX(
		 * -InputContainer.StickOneMax); break; case
		 * KeyEvent.KEYCODE_DPAD_RIGHT:
		 * m_inputContainer.getMovementDirection().setX(
		 * InputContainer.StickOneMax); break; } return true;
		 */
		boolean handled = false;

		int odid = event.getDeviceId();
		InputContainer matchingCont = m_inputContainer.get(Integer
				.valueOf(odid));

		if (matchingCont == null)
			// device has not been mapped
			return false;

		if (keyCode >= KeyEvent.KEYCODE_DPAD_UP
				&& keyCode <= KeyEvent.KEYCODE_DPAD_RIGHT) {
			if ((event.getSource() & InputDevice.SOURCE_DPAD) != 0) {
				// Event is from actual dpad, giving directions
				Vector2 oldMovement = matchingCont.getMovementDirection();
				if (keyCode == KeyEvent.KEYCODE_DPAD_UP) {
					oldMovement.setY(oldMovement.y()
							+ InputContainer.StickOneMax);
				}
				if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
					oldMovement.setY(oldMovement.y()
							- InputContainer.StickOneMax);
				}
				if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT) {
					oldMovement.setX(oldMovement.x()
							- InputContainer.StickOneMax);
				}
				if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
					oldMovement.setX(oldMovement.x()
							+ InputContainer.StickOneMax);
				}
			}
		} else {
/*
			// Handle the input
			switch (keyCode) {
			case OuyaController.BUTTON_O:
				// You now have the key pressed and the player # that pressed it
				// doSomethingWithKey();
				matchingCont.setKeyDownKick(true);
				handled = true;
				break;

			case OuyaController.BUTTON_A:
				// You now have the key pressed and the player # that pressed it
				// doSomethingWithKey();
				matchingCont.setKeyDownJump(true);
				handled = true;
				break;

			case OuyaController.BUTTON_Y:
				// You now have the key pressed and the player # that pressed it
				// doSomethingWithKey();
				matchingCont.KeyDownDebug1 = true;
				handled = true;
				break;

			case OuyaController.BUTTON_MENU:
				// You now have the key pressed and the player # that pressed it
				// doSomethingWithKey();
				matchingCont.setKeyDownMenu(true);
				handled = true;
				break;
			}*/
		}

		return handled || super.onKeyDown(keyCode, event);
	}

	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {

		int odid = event.getDeviceId();
		InputContainer matchingCont = m_inputContainer.get(Integer
				.valueOf(odid));

		switch (keyCode) {

		case KeyEvent.KEYCODE_DPAD_UP:
			Log.e(TAG, "up un-pressed");
			matchingCont.getMovementDirection().setY((float) 0.0);
			break;
		case KeyEvent.KEYCODE_DPAD_DOWN:
			matchingCont.getMovementDirection().setY((float) 0.0);
			break;
		case KeyEvent.KEYCODE_DPAD_LEFT:
			matchingCont.getMovementDirection().setX((float) 0.0);
			break;
		case KeyEvent.KEYCODE_DPAD_RIGHT:
			matchingCont.getMovementDirection().setX((float) 0.0);
			break;
		}

		return true;
	}

	// todo: fix this, does this work. how to quit the application ?
	@Override
	protected void onPause() {
		JavaLog.info(TAG, "onPause called");
		super.onPause();
		m_soundBackend.pauseSound();
		m_view.onPause();
	}

	@Override
	protected void onResume() {
		JavaLog.info(TAG, "onResume called");
		super.onResume();
		m_soundBackend.resumeSound();
		m_view.onResume();
	}

	@Override
	protected void onStop() {
		JavaLog.info(TAG, "onStop called");
		// disabled for debugging
		//unregisterReceiver(m_shutdownReceiver);
		super.onStop();
	}
}
