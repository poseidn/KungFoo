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

import com.fast.descent.resources.FileBackend;
import com.fast.descent.sound.SoundBackend;

import java.io.IOException;

import javax.microedition.khronos.opengles.GL10;

// Wrapper for native library

public class DescentLib {

	static String TAG = "DescentLib";

	static {
		System.loadLibrary("FastDescent");
	}

	private SoundBackend m_soundBackend;
	private FileBackend m_fileBackend;

	public DescentLib(SoundBackend soundBackend, FileBackend fileBackend) {
		m_soundBackend = soundBackend;
		m_fileBackend = fileBackend;
	}

	// C++ functions made available to Java side
	public native void initEngines(int width, int height);

	public native void initGame();

	public native boolean isInitialized();

	public native void androidOnResume();
	
	public native void step(float deltaT);

	public native void registerTexture(String name, int OpenGLid, int frameCount);

	public native void injectDirectionStickOne(int devId, float x, float y);

	public native void injectKeyDown(int devId, int keyId);

	public native void registerInputDevice(int devId);

	public native void setVirtualControls();

	public native float getTileSizeX();

	public native float getTileSizeY();

	// Java methods made available to the C++ side
	
	// will be called to load levels, for example
	public String readTextFile(String name) {
		String result = m_fileBackend.readTextFile(name);
		JavaLog.info(TAG, "Java: Level loaded " + name);
		return result;
	}

	public int playSound(String name, float direction) {
		return m_soundBackend.playSound(name, direction);
	}

	public int playMusic(String name) {
		return m_soundBackend.playMusic(name);
	}

	public void stopPlay(int playId, float fadeOutTime) {
		m_soundBackend.stopPlay(playId);
	}

	public int loadImage(String imageName) {
		int id;

		try {
			id = m_fileBackend.loadTexture(imageName);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return 0;
		}
		return id;
	}

	// sets the correct openGl context for the Java-side file backend
    // which is used if textures get loaded from the C++ side
	public void setCurrentGl(GL10 gl) {
		m_fileBackend.setCurrentGl(gl);
	}
}
