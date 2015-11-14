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
		SDL_Delay( round( waitMS));
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

