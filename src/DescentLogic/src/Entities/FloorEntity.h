#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/EntityEngine/SingleVisualEntity.h>

class FloorEntity CPP11_FINAL : public SingleVisualEntity {
public:
	FloorEntity(Vector2 intialPosition, Rectangle2 boundingBox, SpriteVisualRef vis) :
			SingleVisualEntity(intialPosition, boundingBox, vis) {
		setDoesCollide(false);
	}

	virtual ~FloorEntity() {
	}

};

