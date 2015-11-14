#include "EnemyBehaviour.h"


CPP11_CONSTEXPR float EnemyBehaviour::AttackSquaredDistancePlayer = 5.0f * 5.0f;
CPP11_CONSTEXPR float EnemyBehaviour::AttackSquaredDistancePlayerRandomPart = 2.0f;

CPP11_CONSTEXPR float EnemyBehaviour::StopAttackSquaredDistancePlayer = 10.0f * 10.0f;

CPP11_CONSTEXPR float EnemyBehaviour::HitTime = 0.5f;
CPP11_CONSTEXPR float EnemyBehaviour::MaxSpeed = 6.0f;
CPP11_CONSTEXPR float EnemyBehaviour::AttacDelay = 0.5f;
CPP11_CONSTEXPR float EnemyBehaviour::RegenerationAfterHit = 0.4f;

CPP11_CONSTEXPR float EnemyBehaviour::ClosestApproach = 0.6f;
CPP11_CONSTEXPR float EnemyBehaviour::KickDistancePlayer = 0.7f;

CPP11_CONSTEXPR float EnemyFatBehaviour:: HitTime = 0.5f;
CPP11_CONSTEXPR float  EnemyFatBehaviour::MaxSpeed = 3.0f;
CPP11_CONSTEXPR float EnemyFatBehaviour::AttacDelay = 0.5f;
CPP11_CONSTEXPR float EnemyFatBehaviour::RegenerationAfterHit = 0.4f;

CPP11_CONSTEXPR int EnemyFatBehaviour::Life = 25;

CPP11_CONSTEXPR float EnemyFatBehaviour::ClosestApproach = 0.6f;
CPP11_CONSTEXPR float EnemyFatBehaviour::KickDistancePlayer = 0.7f;

