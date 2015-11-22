package com.fast.descent.resources;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;

import com.fast.descent.JavaLog;

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

		GLES20.glBindTexture(GL10.GL_TEXTURE_2D, id);

		// Generate, and load up all of the mipmaps:
		// todo: we don't need that many levels, this will only eat up time
		for (int level = 0, height = bmp.getHeight(), width = bmp.getWidth(); true; level++) {
			JavaLog.info("Descent", "Creating level " + level);
			// Push the bitmap onto the GPU:
			GLUtils.texImage2D(GL10.GL_TEXTURE_2D, level, bmp, 0);

			// We need to stop when the texture is 1x1:
			if (height == 1 && width == 1)
				break;

			// Resize, and let's go again:
			width >>= 1;
			height >>= 1;
			if (width < 1)
				width = 1;
			if (height < 1)
				height = 1;

			Bitmap bmp2 = Bitmap.createScaledBitmap(bmp, width, height, true);
			bmp.recycle();
			bmp = bmp2;
		}

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
