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
