package com.fast.descent;

import android.app.NativeActivity;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLUtils;
import android.os.Bundle;
import android.os.Vibrator;

import com.fast.descent.resources.FileBackend;
import com.fast.descent.sound.SoundBackend;
import com.fast.descent.exceptions.ResourceNotFound;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.microedition.khronos.opengles.GL10;

public class DescentNativeActivity extends NativeActivity {
	public void someCall() {
		JavaLog.info("DescentNativeActivity", "someCall called");
	}

	private static int newTextureID(GL10 gl) {
		int[] temp = new int[1];
		gl.glGenTextures(1, temp, 0);
		return temp[0];
	}

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		m_fileBackend = new FileBackend(this);
		m_soundBackend = new SoundBackend(this);
	}

	FileBackend m_fileBackend = null;
	SoundBackend m_soundBackend = null;

	// forwards to FileBackend
	public int loadImage(String imageName) throws IOException {
		return m_fileBackend.loadTexture(imageName);
	}

	public void freeTexture(int textureId) {
		m_fileBackend.freeTexture(textureId);
	}

	// forwards to SoundBackend
	public int playMusic(String name) throws ResourceNotFound {
		return m_soundBackend.playMusic(name);
	}

	public int playSound(String name, float direction) throws ResourceNotFound {
		return m_soundBackend.playSound(name, direction);
	}

	public void startVibratePattern(String name) {
		if (name.equals("enemy_punched")) {
			getVibrator().vibrate(200);
		} else if (name.equals("player_out_of_screen")) {
			getVibrator().vibrate(1500);
        } else if (name.equals("player_jump")) {
            // turn on for 100ms, off for 200ms and on for 150ms
            // do not repeat (-1)
            getVibrator().vibrate(new long[]{0, 100, 200, 150},-1);
        }
	}

	public void stopVibratePattern(String name) {
		getVibrator().cancel();
	}

	public void stopAllViberatePatterns() {
		getVibrator().cancel();
	}

	public void stopPlay(int playId) {
		m_soundBackend.stopPlay(playId);
	}

	public void pauseSound() {
		m_soundBackend.pauseSound();
	}

	public void resumeSound() {
		m_soundBackend.resumeSound();
	}

	private Vibrator getVibrator() {
		return (Vibrator) getSystemService(VIBRATOR_SERVICE);
	}
}
