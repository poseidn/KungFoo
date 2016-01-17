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

#pragma once

#include <boost/noncopyable.hpp>
#include "../Log.h"

class TimeSliceAction: boost::noncopyable {
public:

	TimeSliceAction() :
			m_timeLeft(0.0f), m_cooldown(-1.0f), m_isActive(false), m_justDisabledCheck(false), m_wasProcessed(
					false) {

	}

	void activate(const float jumpTime) {
		m_isActive = true;
		m_wasProcessed = false;
		m_timeLeft = jumpTime;
	}

	void validate(const float deltaT, const float cooldown = 0.0f) {
		if (m_isActive) {
			m_timeLeft -= deltaT;
			if (m_timeLeft < 0.0f) {
				reset();
				m_justDisabledCheck = true;
				if (cooldown > 0.0f)
					m_cooldown = cooldown;
			}
		}

		if (m_cooldown > 0.0f) {
			m_cooldown -= deltaT;
		}
	}

	bool isActive() const {
		return m_isActive;
	}

	bool wasJustDisabled() {
		if (m_justDisabledCheck) {
			m_justDisabledCheck = false;
			return true;
		}
		return false;
	}

	bool wasProcessed() const {
		return m_wasProcessed;
	}

	void setProcessed() {
		m_wasProcessed = true;
	}

	void reset() {
		m_isActive = false;
		m_wasProcessed = false;
		m_timeLeft = 0.0f;
	}

	bool canActivate() const {
		return (!isActive() && (m_cooldown <= 0.0f));
	}
private:
	float m_timeLeft;
	float m_cooldown;
	bool m_isActive;
	bool m_justDisabledCheck;
	// will be set to true, once the action has been proceesed, like the result of a
	// kick has been appplied to the game state
	// this does not mean that the action is over yet, the animation etc. is still running
	bool m_wasProcessed;
};

