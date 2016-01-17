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

#include <boost/math/constants/constants.hpp>

class PlayerMovement {
public:
	// maximum speed the player is allowed to move ( when not jumping )
	  const static float MaxSpeed  ;
	// the part which decais the movement which is dependent of the ratio between
	// current movement and max speed
	  const  static float MovementDecayDynamic;
	// the constant part which is always removed from the player speed
	// the bigger, the more speed is removed
	  const 	  static float MovementDecayStatic;

	  const  static float MaxStuckAngle;

	  const static float AttackRange;
	  const static float AttackRangeSquared;

	// opens up a 180 degree field infront of the player to attack
	  const static float AttackAngle;

	// how many enemies can be affected by one player kick at a time
	  const static size_t KickAffectCount;

	  const static float JumpTime;
	  const static float JumpIncreaseSpeedFactor;

	  const static float HitRegenTime;

	//constexpr static float KickTime = 0.36f;
	  const static float KickTime;
	  const static int KickSubtractLife;
	  const static float HitKickBackFactor;

	  const  static float BikingCooldown;
	  const  static float BikingTime;
	  const static float BikingMaxMovement;

	// the time which have to be waited afer one jump before the next
	// one can be performed
	  const static float JumpRegenerationTime;

	// the maximum number of fields which the player is allowed to advance infront of the camera
	// limits the players to not run "away" from the camera
	  const static float MaxAdvance;
};
