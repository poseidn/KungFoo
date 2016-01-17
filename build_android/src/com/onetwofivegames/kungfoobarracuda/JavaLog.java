package com.onetwofivegames.kungfoobarracuda;

import android.util.Log;

public class JavaLog {
	public static void fatal(String tag, String message) {
		Log.e(tag, message);
	}

	public static void info(String tag, String message) {
		Log.i(tag, message);
	}
}
