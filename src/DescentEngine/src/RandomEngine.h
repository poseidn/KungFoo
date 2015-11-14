#pragma once

//#ifdef USE_SDL
//#include <SDL/SDL.h>
#include <random>
#include <sstream>
#include <math.h>
#include "VectorTypes.h"
//#endif

//#include <a>

class RandomEngine {
public:
	typedef std::pair<int, int> SpanInt;
	typedef std::pair<float, float> SpanFloat;

//#ifdef USE_SDL
	// todo: find the fastest rng in c++11
	std::default_random_engine m_engine;
//#endif

	int randomInt(SpanInt s) {

//#ifdef USE_SDL
		std::uniform_int_distribution<int> int_dist10(s.first, s.second);
		int rn = int_dist10(m_engine);
		return rn;
//#else
//		return s.first;
//#endif
	}

	Vector2 randomAbovePoint(Vector2 const& center, float radius) {
		std::uniform_real_distribution<float> pm_AngleDist(-radius, radius);

		//const float pm_Angle = pm_AngleDist(m_engine);
		//const float y = sin(pm_Angle) * radius;
		//const float x = cos(pm_Angle) * radius;

		// x / y is switched on purpose
		Vector2 vecLocal(pm_AngleDist(m_engine), pm_AngleDist(m_engine) + (radius * 1.2f));
		return vecLocal + center;
	}

	float randomFloat(SpanFloat s) {

//#ifdef USE_SDL
		std::uniform_real_distribution<float> float_dist10(s.first, s.second);
		float rn = float_dist10(m_engine);
		return rn;
//#else
//		return s.first;
//#endif
	}

	// gives a random float between 0 and 1
	float randomFloat() {
		return randomFloat(SpanFloat(0.0f, 1.0f));
	}

	std::string randomName(std::string const& baseName, size_t maxAmount) {

		size_t rndI = (size_t) randomInt(SpanInt(1, maxAmount));
		std::stringstream fullName;
		fullName << baseName << rndI;

		return fullName.str();
	}

	float randomFloatNormal(float mean, float stdDev) {

//#ifdef USE_SDL
		std::normal_distribution<float> float_dist10(mean, stdDev);
		float rn = float_dist10(m_engine);
		return rn;
//#else
//		return s.first;
//#endif
	}

};
