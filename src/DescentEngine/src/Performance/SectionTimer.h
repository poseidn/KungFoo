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

#include <unordered_map>
#include <boost/noncopyable.hpp>
#include <chrono>

#include "../DataTypes/RingBuffer.h"
#include "../Log.h"

#ifdef DESCENT_PROFILE
// todo: average of the last n measurements
class SectionRepo: boost::noncopyable {
public:
	// store up to 1k performance entries
	typedef std::chrono::microseconds Duration;
	typedef RingBuffer<Duration, 10000> Durations;

	void storeResult(std::string const& name, Duration dr);

	void report();

	void clearFile( std::string const& filename);

	void dumpFile( std::string const& filename);

	void clear();

private:
	std::unordered_map<std::string, Durations> m_durations;
};

class SectionTimer: boost::noncopyable {
public:
	SectionTimer(SectionRepo & rep, std::string const& sectionName) :
	m_repo(rep), m_sectionName(sectionName) {
		m_startTime = std::chrono::high_resolution_clock::now();
	}

	~SectionTimer() {
		auto endTime = std::chrono::high_resolution_clock::now();
		m_repo.storeResult(m_sectionName,
				std::chrono::duration_cast < std::chrono::microseconds > (endTime - m_startTime));
	}

private:
	SectionRepo & m_repo;
	std::string m_sectionName;
	std::chrono::high_resolution_clock::time_point m_startTime;

};

#else

class SectionRepo: boost::noncopyable {
public:
	void report() {
	}

	void clearFile( std::string const& filename) {

	}

	void clear() {

	}

	void dumpFile( std::string const& filename) {

	}
};

class SectionTimer: boost::noncopyable {
public:
	SectionTimer(SectionRepo & rep, std::string const& sectionName) {
	}
};

#endif

class GlobalTimingRepo {
public:
	static SectionRepo Rep;
};
