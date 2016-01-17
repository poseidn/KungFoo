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
