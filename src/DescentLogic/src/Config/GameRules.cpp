#include "GameRules.h"

CPP11_CONSTEXPR   float GameRules::DeadTolerance = 2.0f;
CPP11_CONSTEXPR   float  GameRules::DeadPositionTolerance = 0.4f;
CPP11_CONSTEXPR   int  GameRules::PointsForKill = 5;
CPP11_CONSTEXPR   size_t  GameRules::MaxPlayers = 4;
CPP11_CONSTEXPR   float  GameRules::RespawnTime = 15.0f;

// this will need 2 kicks to kill the enemy
CPP11_CONSTEXPR   size_t  GameRules::FighterLife = 10;

CPP11_CONSTEXPR   size_t  GameRules::ScorePerSecond = 1;
// used to place enemies and player entities
CPP11_CONSTEXPR   float  GameRules::GamingPositionLowest = 1.0f;
CPP11_CONSTEXPR   float  GameRules::GamingPositionHighest = 14.0f;

// ok yeah, combos baby !
CPP11_CONSTEXPR   size_t  GameRules::Combo5SingleCount = 5;
CPP11_CONSTEXPR   float  GameRules::Combo5SingleTimeFrame = 4.0f;
CPP11_CONSTEXPR   size_t  GameRules::Combo5SinglePoints = 30;

CPP11_CONSTEXPR   size_t  GameRules::Combo10SingleCount = 10;
CPP11_CONSTEXPR   float  GameRules::Combo10SingleTimeFrame = 6.0f;
CPP11_CONSTEXPR   size_t  GameRules::Combo10SinglePoints = 100;

CPP11_CONSTEXPR   size_t  GameRules::MaxBloodFragments = 200;

CPP11_CONSTEXPR   float  GameRules::DelayedScrolling = 1.5f;

