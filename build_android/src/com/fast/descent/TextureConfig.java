package com.fast.descent;

public class TextureConfig {

	static int DefaultAnimFrameCount = 8;
	public static String DefaultExtension = ".png";

	public TextureConfig(String name, int frameCount) {
		m_name = name;
		m_frameCount = frameCount;
	}

	// only the texture name, without file extension
	public String getName() {
		return m_name;
	}

	public void setName(String m_name) {
		this.m_name = m_name;
	}

	public int getFrameCount() {
		return m_frameCount;
	}

	public void setFrameCount(int m_frameCount) {
		this.m_frameCount = m_frameCount;
	}

	private String m_name;
	private int m_frameCount;
}
