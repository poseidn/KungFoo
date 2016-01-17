/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

package com.onetwofivegames.kungfoobarracuda.resources;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;

import com.onetwofivegames.kungfoobarracuda.JavaLog;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.IntBuffer;

import javax.microedition.khronos.opengles.GL10;

public class FileBackend {

	private static String TAG = "FileBackend";
	private static String ImageFolderName = "images/";

	public FileBackend(Context ctx) {
		m_context = ctx;
	}

	public String readTextFile(String fileName) {
		JavaLog.info(FileBackend.TAG, "Trying to load with full path "
				+ fileName);
		try {
			InputStream streamFile;
			String separator = System.getProperty("line.separator");

			streamFile = m_context.getAssets().open(fileName);
			BufferedReader reader = new BufferedReader(new InputStreamReader(
					streamFile));
			StringBuilder out = new StringBuilder();
			String line;
			while ((line = reader.readLine()) != null) {
				out.append(line);
				// add a newline explicitly, as it is not retured by the
				// readLine() method
				out.append(separator);
			}
			return out.toString();
		} catch (IOException e) {
			JavaLog.fatal(FileBackend.TAG, "cannot load file " + fileName);
			e.printStackTrace();
			return "";
		}
	}

	public int loadTexture(String imageName) throws IOException {

		// In which ID will we be storing this texture?
		int id = newTextureID();

		// This will tell the BitmapFactory to not scale based on the
		// device's pixel density:
		// (Thanks to Matthew Marshall for this bit)
		BitmapFactory.Options opts = new BitmapFactory.Options();
		opts.inScaled = false;

		String fileName = FileBackend.ImageFolderName + imageName;

		JavaLog.info(FileBackend.TAG, "Trying to load with full path "
				+ fileName);
		InputStream streamImageFile = m_context.getAssets().open(fileName);

		// Load up, and flip the texture:
		Bitmap bmp = BitmapFactory.decodeStream(streamImageFile, null, opts);

		streamImageFile.close();

		GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, id);

		GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bmp, 0);
		// by default the min texture filter will use the
		// GL_NEAREST_MIPMAP_LINEAR
		// setting, which uses mip-map, which are not generated and downloaded
		// by this
		// code
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D,
				GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
		bmp.recycle();

		return id;
	}

	public void freeTexture(int textureId) {
		GLES20.glDeleteTextures(1, new int[] { textureId }, 0);
	}

	private static int newTextureID() {
		int[] temp = new int[1];
		GLES20.glGenTextures(1, temp, 0);
		return temp[0];
	}

	private Context m_context;
}
