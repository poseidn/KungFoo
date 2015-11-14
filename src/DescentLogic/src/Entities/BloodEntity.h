#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/EntityEngine/SingleVisualEntity.h>

#include "GameCollisionGroups.h"

class BloodEntity CPP11_FINAL : public SingleVisualEntity {
public:
	BloodEntity(Vector2 intialPosition, Rectangle2 boundingBox, SpriteVisualRef vis) :
			SingleVisualEntity(intialPosition, boundingBox, vis) {
		setCollisionGroup(GameCollisionGroups::Characters);
		setCollisionMask(GameCollisionGroups::Characters_CollidesWith);
	}

	virtual ~BloodEntity() {
	}

	// so they blood will stop moving at some point...
	virtual float getDampingLinear() const CPP11_OVERRIDE {
		return 10.0f;
	}

	virtual CollisionType getCollisionType() const CPP11_OVERRIDE {
		return CollisionType::CircleDynamic;
	}

};
