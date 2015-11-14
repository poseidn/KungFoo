#pragma once

#include <boost/noncopyable.hpp>
#include <string>
#include <vector>
#include <cmath>

#include "../VectorTypes.h"

// contains information about all inputs received by the user.
// this is already abstracted from the concrete device used
class InputContainer /*: boost::noncopyable*/{
public:

	// because we compare to the magSquared of the stick vector...
	static CPP11_CONSTEXPR float StickOneDeadZone;
	// needs to be in sync with the Android InpuContainer
	static CPP11_CONSTEXPR float StickOneMax;

	InputContainer() {
		resetKeypress();
	}

	bool keyDownMenu() const {
		return m_keyDownMenu;
	}

	bool keyDownExit() const {
		return m_keyDownExit;
	}

	bool keyPressDebug1() const {
		return m_keyPressDebug1;
	}

	bool keyPressDebug2() const {
		return m_keyPressDebug2;
	}

	bool keyDownJump() const {
		return m_keyDownJump;
	}

	bool keyDownKick() const {
		return m_keyDownKick;
	}

	bool keyDownBiking() const {
		return m_keyBiking;
	}

	Vector2 const& directionStickOne() const {
		return m_directionStickOne;
	}

	void setDirectionStickOne(Vector2 const& dir) {
		m_directionStickOne = dir;
	}

	// also implements the "dead-space" for analog controllers
	bool isStickOneMoved() const {
		return m_directionStickOne.magSquared() > StickOneDeadZone;
	}

	// the stuff following here is only called by
	// the variuous input implemenations
	void setKeyPressDebug1(bool v) {
		m_keyPressDebug1 = v;
	}

	void setKeyPressDebug2(bool v) {
		m_keyPressDebug2 = v;
	}

	void setKeyDownExit(bool v) {
		m_keyDownExit = v;
	}

	void setKeyDownMenu(bool v) {
		m_keyDownMenu = v;
	}

	void setKeyDownJump(bool v) {
		m_keyDownJump = v;
	}

	void setKeyDownKick(bool v) {
		m_keyDownKick = v;
	}

	void setKeyDownBiking(bool v) {
		m_keyBiking = v;
	}

	void resetKeypress() {
		setKeyPressDebug1(false);
		setKeyPressDebug2(false);
		setKeyDownJump(false);
		setKeyDownKick(false);
		setKeyDownBiking(false);
		setKeyDownMenu(false);
		setKeyDownExit(false);
		m_inputKeys.clear();
	}

	void addInputKey(std::string const& k) {
		m_inputKeys.push_back(k);
	}

	std::vector<std::string> m_inputKeys;

private:
	bool m_keyPressDebug1;
	bool m_keyPressDebug2;
	bool m_keyDownMenu;

	bool m_keyDownJump;
	bool m_keyDownKick;
	bool m_keyDownExit;
	bool m_keyBiking;

	Vector2 m_directionStickOne;
};
