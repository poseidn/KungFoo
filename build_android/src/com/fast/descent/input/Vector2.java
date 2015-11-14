package com.fast.descent.input;

public class Vector2 {

	public Vector2() {
		m_x = (float) 0.0;
		m_y = (float) 0.0;
	}

	public Vector2(float x, float y) {
		m_x = x;
		m_y = y;
	}

	public static Vector2 Unit() {
		return new Vector2(0, 0);
	}

	public float x() {
		return m_x;
	}

	public void setX(float m_x) {
		this.m_x = m_x;
	}

	public float y() {
		return m_y;
	}

	public void setY(float m_y) {
		this.m_y = m_y;
	}

	private float m_x;
	private float m_y;
}
