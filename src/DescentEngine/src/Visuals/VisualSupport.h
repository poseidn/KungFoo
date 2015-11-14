#pragma once

#include "../EntityEngine/Entity.h"
#include "ScreenTransform.h"

namespace VisualSupport {

inline void placeXCenter(Entity * ent,
// the relative screen position x ( 0.0 is at the very left )
		float relX,
		// the relative screen position y ( 1.0 is at the very top )
		float relY, ScreenTransform const& trans) {

	const float centerTileX = trans.screenSizeInTiles().x() * relX;
	const float centerHalfTileY = trans.screenSizeInTiles().y() * relY;

	// is automatically centered, because sprite rendering uses the center position
	const float locX = centerTileX;
	//ent->setMoveIntent(Vector2(locX, centerHalfTileY));
	/*std::cout << "locX " << locX << std::endl;
	 std::cout << "ent->getBoundingBox().width() " << ent->getBoundingBox().width() << std::endl;
	 std::cout << "trans.screenSizeInTiles().x() " << trans.screenSizeInTiles().x() << std::endl;
	 std::cout << "Offset " << trans.getOffset().x() << std::endl;*/

	const Vector2 newPos = Vector2(locX, centerHalfTileY);

	ent->setMoveIntent(newPos);
	ent->getActiveVisual().get().setIngame(trans, newPos, false);
}

inline Vector2 positionXCenter(float relX,
// the relative screen position y ( 1.0 is at the very top )
		float relY, ScreenTransform const& trans) {

	const float centerTileX = trans.screenSizeInTiles().x() * relX;
	const float centerTileY = trans.screenSizeInTiles().y() * relY;
	return Vector2(centerTileX, centerTileY);
}

inline void place(Entity * ent,
// the relative screen position x ( 0.0 is at the very left )
		float relX,
		// the relative screen position y ( 1.0 is at the very top )
		float relY, ScreenTransform const& trans) {

	const float centerTileX = trans.screenSizeInTiles().x() * relX;
	const float centerTileY = trans.screenSizeInTiles().y() * relY;
	ent->setMoveIntent(Vector2(centerTileX, centerTileY));
}

}
