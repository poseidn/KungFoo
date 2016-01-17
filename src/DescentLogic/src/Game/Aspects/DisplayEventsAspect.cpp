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

#include "DisplayEventsAspect.h"

#include <sstream>
#include <algorithm>

#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/Visuals/TextSupport.h>
#include <DescentEngine/src/RandomEngine.h>
#include <DescentLogic/src/Entities/EnemyEntity.h>
#include <DescentLogic/src/Config/GameRules.h>
#include <DescentLogic/src/Entities/PlayerEntity.h>

#include "../GameState.h"

#include "../../Common/GameToMenuInfo.h"

void DisplayEventsAspect::init(GameState & gameState) {
	gameState.slotEnemyDied.subscribe([ ] ( GameState & g, PlayerId pid, EnemyEntity * pEnt )
	{
		std::stringstream cmbText;
		cmbText << " " << GameRules::PointsForKill << " ";
		TextSupport::ingameTextFadeOut( g.getEngines(),
				g.getEngines().randomEngine().randomAbovePoint(
						pEnt->getPosition(), 1.5f ), cmbText.str());
	});

	gameState.slotComboDone.subscribe([ ] (GameState & g,PlayerId pid,int enemiesKilld,
			int points, ComboType cmbType ) {
		std::stringstream cmbText;
		cmbText << enemiesKilld << " Combo: " << points;
		PlayerEntity * pEnt = g.getPlayerEntity( pid );
		TextSupport::ingameTextFadeOut( g.getEngines(), g.getEngines().randomEngine().randomAbovePoint(
						pEnt->getPosition(), 1.5f ), cmbText.str(), 1.2f );
	});
}

