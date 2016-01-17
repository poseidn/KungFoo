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

#include <DescentEngine/src/Cpp11.h>

class EnemyBehaviour {
public:

	// the squared distance to the player, where enemies will start to attack the player
	CPP11_CONSTEXPR static float AttackSquaredDistancePlayer;
	CPP11_CONSTEXPR static float AttackSquaredDistancePlayerRandomPart;

	CPP11_CONSTEXPR static float StopAttackSquaredDistancePlayer;

	CPP11_CONSTEXPR static float HitTime;
	CPP11_CONSTEXPR static float MaxSpeed;
	CPP11_CONSTEXPR static float AttacDelay;
	CPP11_CONSTEXPR static float RegenerationAfterHit;

	CPP11_CONSTEXPR static float ClosestApproach;
	CPP11_CONSTEXPR static float KickDistancePlayer;

	/* problem when compiling with clang
	 * CPP11_CONSTEXPR   int MinEnemiesPerSegment = 1;
	 CPP11_CONSTEXPR int MaxEnemiesPerSegment = 6;*/

};

class EnemyFatBehaviour {
public:
	CPP11_CONSTEXPR static float HitTime;
	CPP11_CONSTEXPR static float MaxSpeed;
	CPP11_CONSTEXPR static float AttacDelay;
	CPP11_CONSTEXPR static float RegenerationAfterHit;

	CPP11_CONSTEXPR static int Life;

	CPP11_CONSTEXPR static float ClosestApproach;
	CPP11_CONSTEXPR static float KickDistancePlayer;

	/* problem when compiling with clang
	 * CPP11_CONSTEXPR   int MinEnemiesPerSegment = 1;
	 CPP11_CONSTEXPR int MaxEnemiesPerSegment = 6;*/

};
