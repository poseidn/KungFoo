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
