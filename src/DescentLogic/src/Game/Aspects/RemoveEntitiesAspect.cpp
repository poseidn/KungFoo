#include "RemoveEntitiesAspect.h"

#include <DescentEngine/src/EntityEngine/EntityFactory.h>
#include <DescentEngine/src/Visuals/TextVisual.h>
#include <DescentEngine/src/EntityEngine/SingleVisualEntity.h>

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"
#include "../../Entities/BloodEntity.h"

#include "../../Entities/EnemyEntity.h"
#include "../../Common/ChangeToGameInfo.h"
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
