#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/EntityEngine/SingleVisualEntity.h>

#include "GameCollisionGroups.h"

class WallEntity CPP11_FINAL : public SingleVisualEntity {
public:
	WallEntity(Vector2 intialPosition, Rectangle2 boundingBox, SpriteVisualRef vis) :
			SingleVisualEntity(intialPosition, boundingBox, vis) {
		setDoesCollide(false);
	}

	virtual ~WallEntity() {
	}
};
