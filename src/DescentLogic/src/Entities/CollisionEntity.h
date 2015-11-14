#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/EntityEngine/SingleVisualEntity.h>

#include "GameCollisionGroups.h"

class CollisionEntity: public Entity {
public:
	CollisionEntity(Vector2 intialPosition, Rectangle2 boundingBox) :
			Entity(intialPosition, boundingBox) {

		setCollisionGroup(GameCollisionGroups::Statics);
		setCollisionMask(GameCollisionGroups::Statics_CollidesWith);

	}

	virtual ~CollisionEntity() {
	}

	virtual CollisionType getCollisionType() const CPP11_OVERRIDE {
		return CollisionType::BoxStatic;
	}

	virtual bool isStatic() const CPP11_OVERRIDE {
		return true;
	}
};

