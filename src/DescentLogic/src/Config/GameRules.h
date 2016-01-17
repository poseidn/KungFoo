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

#include <cstddef>

#include <DescentEngine/src/Cpp11.h>

class GameRules {
public:
	CPP11_CONSTEXPR static float DeadTolerance;
	CPP11_CONSTEXPR static float DeadPositionTolerance;
	CPP11_CONSTEXPR static int PointsForKill;
	CPP11_CONSTEXPR static size_t MaxPlayers;
	CPP11_CONSTEXPR static float RespawnTime;

	// this will need 2 kicks to kill the enemy
	CPP11_CONSTEXPR static size_t FighterLife;

	CPP11_CONSTEXPR static size_t ScorePerSecond;
	// used to place enemies and player entities
	CPP11_CONSTEXPR static float GamingPositionLowest;
	CPP11_CONSTEXPR static float GamingPositionHighest;

	// ok yeah, combos baby !
	CPP11_CONSTEXPR static size_t Combo5SingleCount;
	CPP11_CONSTEXPR static float Combo5SingleTimeFrame ;
	CPP11_CONSTEXPR static size_t Combo5SinglePoints;

	CPP11_CONSTEXPR static size_t Combo10SingleCount;
	CPP11_CONSTEXPR static float Combo10SingleTimeFrame;
	CPP11_CONSTEXPR static size_t Combo10SinglePoints ;
	
	CPP11_CONSTEXPR static size_t MaxBloodFragments;

	CPP11_CONSTEXPR static float DelayedScrolling;

	/*
	 * not impemented yet
	 CPP11_CONSTEXPR static size_t Combo10MultiCount = 10;
	 CPP11_CONSTEXPR static float Combo10MultiTimeFrame = 6.0f;
	 CPP11_CONSTEXPR static size_t Combo10MultiPoints = 50;
	 */
};
