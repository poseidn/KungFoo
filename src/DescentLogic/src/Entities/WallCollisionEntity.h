#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/EntityEngine/SingleVisualEntity.h>

#include "CollisionEntity.h"

class WallCollisionEntity CPP11_FINAL : public CollisionEntity {
public:
	WallCollisionEntity(Vector2 intialPosition, Rectangle2 boundingBox) :
			CollisionEntity(intialPosition, boundingBox) {
	}

	virtual ~WallCollisionEntity() {
	}
};
