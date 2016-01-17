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

class TickAction: boost::noncopyable {
public:
	// tick in seconds
	TickAction(float tick = 1.0f) :
			m_tick(tick), m_sumTick(0.0f) {

	}

	// if returned true, the time interval given with "tick" has been crossed
	bool validate(const float dt) {
		m_sumTick += dt;
		if (m_sumTick >= m_tick) {
			m_sumTick -= m_tick;
			return true;
		}
		return false;
	}

private:
	const float m_tick;
	float m_sumTick;
};
