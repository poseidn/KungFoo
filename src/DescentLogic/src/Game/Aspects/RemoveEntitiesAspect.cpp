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

#include "RemoveEntitiesAspect.h"

#include <DescentEngine/src/EntityEngine/EntityFactory.h>
#include <DescentEngine/src/Visuals/TextVisual.h>
#include <DescentEngine/src/EntityEngine/SingleVisualEntity.h>

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"
#include "../../Entities/BloodEntity.h"

#include "../../Entities/EnemyEntity.h"
#include <DescentEngine/src/StateEngine/StateChangeInfo.h>
#include "../Util/SafePlacement.h"

void RemoveEntitiesAspect::init(GameState & gameState) {

	gameState.slotStep.subscribe(
			[] ( GameState & gs, float dt )
			{
				const Vector3 camLoc = gs.getEngines().renderEngine().getCameraLocation();

				auto enemyList = gs.getEnemies();
				for (EnemyEntity * en : enemyList) {

					if ( en->getPosition().y() < ( camLoc.y() - 15.0f) ) {
						logging::Info() << "Removing enemy at " << en->getPosition() << "because it is out of camera view";
						gs.removeEnemyEntity( en );
						gs.getEngines().entityEngine().removeEntity(static_cast<Entity *>(en), gs.getEngines());
					}
				}

				// always remove and the oldest entries and leave 50
				// in place. This looks good when the blood in visible
				// in the menu screen
				auto & fragList = gs.getFragemts();
				while ( fragList.size() > GameRules::MaxBloodFragments ) {
					// remove first
					//gs.remove

					auto fs = fragList.front();

					gs.getEngines().entityEngine().removeEntity(static_cast<Entity*>(fs), gs.getEngines() );
					fragList.pop_front();
				}
				/*				for (BloodEntity * en : fragList) {

				 *			}*/

			}, "RemoveEntitiesAspect.step");
}
