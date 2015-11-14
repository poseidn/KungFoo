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
