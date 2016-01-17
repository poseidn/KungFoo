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

#include <DescentEngine/src/Engines.h>
#include <DescentLogic/src/Game/GameState.h>
#include <DescentLogic/src/Config/GameRules.h>
#include <DescentLogic/src/Entities/PlayerEntity.h>
#include <DescentLogic/src/Entities/EnemyEntity.h>

namespace game_util {

inline bool willFit(Vector2 const& position, const float entityRadius, Engines & engines, GameState & gs) {

	auto & statics = gs.getEngines().entityEngine().getStaticEntities();

	//logging::Info() << "willFit: checking pos " << position;

	// never fit outside of the defined borders
	if ((position.x() < GameRules::GamingPositionLowest) || (position.x() > GameRules::GamingPositionHighest))
		return false;

	// check statics
	for (auto & sEnt : statics) {
		if (sEnt->doesCollide()) {
			const Vector2 conAtoB = sEnt->getPosition() - position;
			const float conDist = conAtoB.mag();
			if (conDist < (entityRadius + sEnt->getCollisionRadius())) {
				// that's a collision
				//logging::Info() << "found collision";
				return false;
			}

		}
	}

	GameState::EnemyList const& enemies = gs.getEnemies();
	// check enemies
	for (EnemyEntity * sEnt : enemies) {
		if (sEnt->doesCollide()) {
			const Vector2 conAtoB = sEnt->getPosition() - position;
			const float conDist = conAtoB.mag();
			if (conDist < (entityRadius + sEnt->getCollisionRadius())) {
				// that's a collision
				//logging::Info() << "found collision";
				return false;
			}

		}
	}

	// check other players
	for (PlayerData & pd : gs.getPlayers()) {
		PlayerEntity * sEnt = pd.Entity;
		if (sEnt != nullptr) {
			if (sEnt->doesCollide()) {
				const Vector2 conAtoB = sEnt->getPosition() - position;
				const float conDist = conAtoB.mag();
				if (conDist < (entityRadius + sEnt->getCollisionRadius())) {
					// that's a collision
					//logging::Info() << "found collision";
					return false;
				}
			}
		}
	}

	// todo: also check enemies and player
	//logging::Info() << "found here";

	// no collision
	return true;

}

inline std::pair<bool, Vector2> findSafePlacement(Vector2 const& idealPosition, const float entityRadius,
		const float maxRadius, Engines & engines, GameState & gs) {

	// circle around the ideal position ...

	// make sure, nothing is outside of the game field
	//logging::Info() << "looking for safe placement at " << idealPosition;

	const float radiusIncrease = 1.0f;
	bool first = true;

	for (float radius = 0.0f; radius <= maxRadius; radius += radiusIncrease) {
		if (first) {
			// check the actual place
			const bool fits = willFit(idealPosition, entityRadius, engines, gs);
			if (fits) {
				//logging::Info() << "fits at " << idealPosition;
				return std::make_pair(true, idealPosition);
			}

			first = false;
		} else {
			// check in 1/8th circle
			// a bit bigger to make sure our sketchy for loop with floats will work...
			const float piFourth = boost::math::constants::pi<float>() * 0.27f;
			const float piTimesTwo = boost::math::constants::pi<float>() * 2.0f;

			for (float curPi = 0; curPi < piTimesTwo; curPi += piFourth) {
				const Vector2 newPosition(idealPosition.x() + (radius * sin(curPi)),
						idealPosition.y() - (radius * cos(curPi)));

				const bool fits = willFit(newPosition, entityRadius, engines, gs);
				if (fits) {
					//logging::Info() << "fits at " << newPosition;
					return std::make_pair(true, newPosition);
				}
			}
		}
	}

// no way found, sorry ...
	return std::make_pair(false, Vector2());
}

}
