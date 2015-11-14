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
