#pragma once

#include "Entity.h"

class MoveAccessClass {
public:
	static void setPosition(Entity & ent, Vector2 const& pos) {
		ent.setPosition(pos);
	}

	static void applyMoveIntent(Entity & ent) {
		ent.applyMoveIntent();
	}
};
