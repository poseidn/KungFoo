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

#include <chrono>
#include <boost/noncopyable.hpp>

namespace chr = std::chrono;

class TimingBase: boost::noncopyable {
public:
	TimingBase() {
		start();
	}

	void start() {
		m_startTime = chr::high_resolution_clock::now();
	}

	// in s
	float delta() const {
		std::chrono::milliseconds secs = chr::duration_cast < std::chrono::milliseconds
				> (m_endTime - m_startTime);
		return secs.count() * 0.001f;
	}

	float end() {
		m_endTime = chr::high_resolution_clock::now();
		return delta();
	}

private:
	chr::high_resolution_clock::time_point m_startTime;
	chr::high_resolution_clock::time_point m_endTime;
};

#ifdef USE_SDL
#include <cmath>
#include "SDL_include.h"

class SDLTiming: public TimingBase
{
public:
	SDLTiming() : TimingBase()
	{

	}

	// tm in seconds
	static void wait ( float waitSeconds )
	{
		// with take ms
		float waitMS = waitSeconds * 1000.0f;
		SDL_Delay( std::round( waitMS));
	}

};

class Timing: public SDLTiming {
};

#endif

#ifdef USE_ANDROID

#include <unistd.h>

class AndroidTiming: public TimingBase
{

public:
	AndroidTiming() : TimingBase() {
	}

	static void wait ( long tm ) {
		usleep(tm);
	}

};

class Timing: public AndroidTiming {
};

#endif

