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
