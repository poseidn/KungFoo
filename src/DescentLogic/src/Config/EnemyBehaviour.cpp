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

