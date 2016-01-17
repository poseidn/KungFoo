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

#include <string>
#include <map>
#include <list>
#include <vector>
#include <memory>
#include <functional>

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "Log.h"
#include "Timing.h"
#include "Performance/SectionTimer.h"

// allows to optionally report the timing for each of the signal calls
//#define DESCENT_SIGNAL_PROFILE

namespace slots {

typedef std::list<float> TimingQueue;

typedef std::pair<std::string, float> TimingResult;
typedef std::vector<TimingResult> TimingResultList;

template<typename ... Args>
class Slot {
public:
	typedef std::function<void(Args...)> func_type;

	class SlotFunction: boost::noncopyable {
	public:
		SlotFunction(std::string const& name, func_type func) :
				m_function(func)
#ifdef DESCENT_SIGNAL_PROFILE
		, m_name(name)
#endif

		{

		}

		func_type getFunction() const {
			return m_function;
		}

	private:

		func_type m_function;

#ifdef DESCENT_SIGNAL_PROFILE
	public:
		std::string m_name;
		std::string const& getName() const
		{
			return m_name;
		}
#endif

	};

	// todo: how to do func pointer when we dont have the fat stl ?
	//typedef void(int) * old_func_ptr;

	// name will not be stored, if the signal profiling is not enabled
	void subscribe(func_type f, std::string name = "") {
		m_functions.push_back(new SlotFunction(name, f));
	}

	void signal(Args ... args) {
		for (auto const& f : m_functions) {
			//logging::Debug() << "signaling";
#ifdef DESCENT_SIGNAL_PROFILE
			Timing t;
#endif

			{
#ifdef DESCENT_SIGNAL_PROFILE
				SectionTimer tm(GlobalTimingRepo::Rep, "signal." + f.getName());
#endif
				f.getFunction()(args...);
			}

#ifdef DESCENT_SIGNAL_PROFILE

			addTiming(f.getName(), t.end());
#endif
		}
	}

private:
	boost::ptr_vector<SlotFunction> m_functions;

#ifdef DESCENT_SIGNAL_PROFILE

public:

	TimingResultList getTimingResultList() const {
		TimingResultList timingRes;

		timingRes.reserve(m_timings.size());

		for (auto tPairIt = m_timings.begin(); tPairIt != m_timings.end(); tPairIt++) {
			const float avg = average(tPairIt->second);
			timingRes.push_back(TimingResult(tPairIt->first, avg));
		}

		return timingRes;
	}

private:

	void addTiming(std::string name, float t) {
		TimingQueue & tq = m_timings[name];
		while (tq.size() > MaxTimingsCached) {
			tq.pop_front();
		}
		tq.push_back(t);
	}

	template<class TIterable>
	float average(TIterable const & theList) const {
		if (theList.size() == 0)
		return 0.0f;

		float sum = 0.0f;
		for (auto it = theList.begin(); it != theList.end(); it++) {
			sum += (*it);
		}
		return sum / theList.size();
	}

	std::map<std::string, TimingQueue> m_timings;
	constexpr static size_t MaxTimingsCached = 10;
#endif
};

}
