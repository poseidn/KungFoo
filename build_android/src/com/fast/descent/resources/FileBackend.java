package com.fast.descent.resources;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLUtils;

import com.fast.descent.JavaLog;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

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
			String separator = System.getProperty( "line.separator" );

			streamFile = m_context.getAssets().open(fileName);
			BufferedReader reader = new BufferedReader(new InputStreamReader(
					streamFile));
			StringBuilder out = new StringBuilder();
			String line;
			while ((line = reader.readLine()) != null) {
				out.append(line);
				// add a newline explicitly, as it is not retured by the readLine() method
				out.append( separator );
			}
			return out.toString();
		} catch (IOException e) {
			JavaLog.fatal(FileBackend.TAG, "cannot load file " + fileName);
			e.printStackTrace();
			return "";
		}
	}

	public void setCurrentGl(GL10 gl) {
		m_currentGl = gl;
	}

	public int loadTexture(String imageName) throws IOException {

		// In which ID will we be storing this texture?
		int id = newTextureID(m_currentGl);

		// We need to flip the textures vertically:
		// Matrix flip = new Matrix();
		/* flip.postScale(1f, -1f); */

		// This will tell the BitmapFactory to not scale based on the
		// device's pixel density:
		// (Thanks to Matthew Marshall for this bit)
		BitmapFactory.Options opts = new BitmapFactory.Options();
		opts.inScaled = false;

		String fileName = FileBackend.ImageFolderName + imageName;
		// has already been set by calling code
		// + TextureConfig.DefaultExtension;

		JavaLog.info(FileBackend.TAG, "Trying to load with full path "
				+ fileName);
		InputStream streamImageFile = m_context.getAssets().open(fileName);

		// Load up, and flip the texture:
		Bitmap bmp = BitmapFactory.decodeStream(streamImageFile, null, opts);

		streamImageFile.close();
		/*
		 * Bitmap bmp = Bitmap.createBitmap(temp, 0, 0, temp.getWidth(),
		 * temp.getHeight(), flip, true);
		 */

		m_currentGl.glBindTexture(GL10.GL_TEXTURE_2D, id);

		// Set all of our texture parameters:
		// produces error on Nexus and seems not to be needed
		/*m_currentGl.glTexParameterf(GL10.GL_TEXTURE_2D,
				GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_LINEAR_MIPMAP_NEAREST);
		m_currentGl.glTexParameterf(GL10.GL_TEXTURE_2D,
				GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR_MIPMAP_NEAREST);
		m_currentGl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,
				GL10.GL_REPEAT);
		m_currentGl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,
				GL10.GL_REPEAT);*/

		// Generate, and load up all of the mipmaps:
		for (int level = 0, height = bmp.getHeight(), width = bmp.getWidth(); true; level++) {
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
		// temp.recycle();

		return id;
	}

	private static int newTextureID(GL10 gl) {
		int[] temp = new int[1];
		gl.glGenTextures(1, temp, 0);
		return temp[0];
	}

	private Context m_context;
	private GL10 m_currentGl;
}
