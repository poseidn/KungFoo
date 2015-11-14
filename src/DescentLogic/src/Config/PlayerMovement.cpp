
#include "PlayerMovement.h"

// maximum speed the player is allowed to move ( when not jumping )
const   float PlayerMovement::MaxSpeed = 13.0f;
// the part which decais the movement which is dependent of the ratio between
// current movement and max speed
const   float PlayerMovement::MovementDecayDynamic = 0.00f;
// the constant part which is always removed from the player speed
// the bigger, the more speed is removed
const   float PlayerMovement::MovementDecayStatic = 4.0f;

const   float PlayerMovement::MaxStuckAngle = boost::math::constants::pi<float>() * 0.6f;

const   float PlayerMovement::AttackRange = 1.7f;
const   float PlayerMovement::AttackRangeSquared = AttackRange * AttackRange;

// opens up a 180 degree field infront of the player to attack
const   float PlayerMovement::AttackAngle = 3.1415f * (1.0f / 2.0f);

// how many enemies can be affected by one player kick at a time
const   size_t PlayerMovement::KickAffectCount = 2;

const   float PlayerMovement::JumpTime = 0.36f;
const   float PlayerMovement::JumpIncreaseSpeedFactor = 1.34f;

const   float PlayerMovement::HitRegenTime = 1.0f;

//constexpr static float KickTime = 0.36f;
const   float PlayerMovement::KickTime = 0.11f;
const   int PlayerMovement::KickSubtractLife = 6;
const   float PlayerMovement::HitKickBackFactor = 0.7f;

const   float PlayerMovement::BikingCooldown = 1.0f;
const   float PlayerMovement::BikingTime = 2.5f;
const   float PlayerMovement::BikingMaxMovement = 0.5f;

// the time which have to be waited afer one jump before the next
// one can be performed
const   float PlayerMovement::JumpRegenerationTime = 0.06f;

// the maximum number of fields which the player is allowed to advance infront of the camera
// limits the players to not run "away" from the camera
const   float PlayerMovement::MaxAdvance = 11.0f;

