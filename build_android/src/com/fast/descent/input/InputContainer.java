package com.fast.descent.input;

import com.fast.descent.DescentLib;

public class InputContainer {

	public InputContainer(int devId, boolean useUpdateFromOuya) {
		m_devId = devId;
	}

	// needs to be in-sync with the C++ version
	static public float StickOneMax = (float) 100.0f;

	private Vector2 m_movementDirection = new Vector2();
	private boolean m_keyDownKick = false;
	private boolean m_keyDownJump = false;
	public boolean m_keyDownMenu = false;
	private int m_devId = 0;
	public boolean KeyDownDebug1 = false;

	public int getDevId() {
		return m_devId;
	}

	public Vector2 getMovementDirection() {
		return m_movementDirection;
	}

	public void setMovementDirection(Vector2 m_movementDirection) {
		this.m_movementDirection = m_movementDirection;
	}

	public void setKeyDownKick(boolean v) {
		m_keyDownKick = v;
	}

	public boolean getKeyDownKick() {
		return m_keyDownKick;
	}

	public void setKeyDownJump(boolean v) {
		m_keyDownJump = v;
	}

	public void setKeyDownMenu(boolean v) {
		m_keyDownMenu = v;
	}

	public boolean getKeyDownJump() {
		return m_keyDownJump;
	}

	public void reset() {
		m_keyDownKick = false;
		m_keyDownJump = false;
		m_keyDownMenu = false;
		KeyDownDebug1 = false;
	}

	public void transferInput(DescentLib lib) {
		lib.injectDirectionStickOne(getDevId(), getMovementDirection().x(),
				getMovementDirection().y());

		if (getKeyDownKick()) {
			lib.injectKeyDown(getDevId(), 1);
		}
		if (getKeyDownJump()) {
			lib.injectKeyDown(getDevId(), 2);
		}
		if (KeyDownDebug1) {
			lib.injectKeyDown(getDevId(), 3);
		}
		if (m_keyDownMenu) {
			lib.injectKeyDown(getDevId(), 4);
		}
		/*
		 * if ( getKeyDownJump()) lib.injectKeyJump(1);
		 */
	}
}
