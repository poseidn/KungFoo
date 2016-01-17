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

#include "ComboDetectionAspect.h"

#include <algorithm>
#include <iomanip>
#include <DescentEngine/src/VectorTypes.h>

#include <DescentEngine/src/Util.h>
#include <DescentEngine/src/Input/InputContainer.h>

#include "../GameState.h"
#include "../../Config/GameRules.h"

#include "../../Entities/PlayerEntity.h"

#include "../../Entities/TextureIds.h"

void ComboDetectionAspect::init(GameState & gs) {
	/*gs.slotStep.subscribe([this] ( GameState & g, float t)
	 {	this->step(g,t);});*/

	gs.slotEnemyDied.subscribe([this] ( GameState & g, PlayerId pid, EnemyEntity * pEnt )
	{
		util::initMap( m_kills, pid );

		PlayerKills & pk = m_kills[pid];

		pk.Kills.push( Kill( g.getTimestamp() ) );

		analyze(g);
	});
}

bool ComboDetectionAspect::bufferEntriesUnused(KillBuffer const& buffer, int bit, int start, int end) {
	for (int i = start; i >= end; i--) {
		if ((buffer.get(i).UsedForCombo & bit) > 0)
			return false;
	}
	return true;
}

void ComboDetectionAspect::markEntriesUsed(KillBuffer & buffer, int bit, int start, int end) {
	for (int i = start; i >= end; i--) {
		buffer.get(i).UsedForCombo |= bit;
	}
}

void ComboDetectionAspect::analyze(GameState & gs) {


	/*static constexpr*/const int Used_5_Single_BitField = 1 << 0;
	/*static constexpr*/const int Used_10_Single_BitField = 1 << 1;
	/*static constexpr*/const int Used_10_Multi_BitField = 1 << 2;


	// iterate over all players
	for (auto & pk : m_kills) {
		KillBuffer & buffer = pk.second.Kills;

		if (buffer.size() >= GameRules::Combo10SingleCount) {
			// what about the time ?
			const int firstEntry = 0;
			const int lastEntry10Combo = -int(GameRules::Combo10SingleCount) + 1;

			const float firstTime = buffer.get(0).Timestamp;
			const float lastTime = buffer.get(lastEntry10Combo).Timestamp;

			const float deltaTime = lastTime - firstTime;
			if ((deltaTime < GameRules::Combo10SingleTimeFrame)
					&& bufferEntriesUnused(buffer, Used_10_Single_BitField, firstEntry, lastEntry10Combo)) {

				//	markEntriesUsed()
				markEntriesUsed(buffer, Used_10_Single_BitField, firstEntry, lastEntry10Combo);
				gs.increaseScore(pk.first, GameRules::Combo10SinglePoints);
				gs.slotComboDone.signal(gs, pk.first, GameRules::Combo10SingleCount,
						GameRules::Combo10SinglePoints, ComboType::Solo);

				logging::Info() << "%%%% 10er single combo detected %%%%";
			}
		}

		// if the player had a 5er combo already, he or she can still get a 10er combo
		if (buffer.size() >= GameRules::Combo5SingleCount) {
			// what about the time ?
			const int firstEntry = 0;
			const int lastEntry5Combo = -int(GameRules::Combo5SingleCount) + 1;

			const float firstTime = buffer.get(0).Timestamp;
			const float lastTime = buffer.get(lastEntry5Combo).Timestamp;

			const float deltaTime = lastTime - firstTime;
			if ((deltaTime < GameRules::Combo5SingleTimeFrame)
					&& bufferEntriesUnused(buffer, Used_5_Single_BitField, firstEntry, lastEntry5Combo)) {

				markEntriesUsed(buffer, Used_5_Single_BitField, firstEntry, lastEntry5Combo);
				gs.increaseScore(pk.first, GameRules::Combo5SinglePoints);
				gs.slotComboDone.signal(gs, pk.first, GameRules::Combo5SingleCount,
						GameRules::Combo5SinglePoints, ComboType::Solo);
				logging::Info() << "%%%% 5er single combo detected %%%%";
			}
		}
	}

	// multiplayer - combos are a lot more tricky to implement
}
