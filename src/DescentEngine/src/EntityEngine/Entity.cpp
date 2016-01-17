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

#include "Entity.h"

#include <Box2D/Box2D.h>

#include "../Engines.h"

#include "../Physics/PhysicsEngine.h"
#include "../Visuals/SpriteVisual.h"

void Entity::unregister(Engines & engines) {
	if ((getRigidBody() != nullptr) && (!isPhysicsAutoRemove())) {
		engines.physicsEngine().unregisterEntity(this, isPhysicsAutoRemove());
	}
}

Entity::~Entity() {
	// do we need to take care of unregistering this,
	// or has it been done already my someone else ?
	/*if (getRigidBody() != nullptr) {
	 delete getRigidBody()->getMotionState();
	 delete getRigidBody()->getCollisionShape();
	 delete getRigidBody();
	 }*/
}

VisualUpdatePair Entity::updateVisual(ScreenTransform const& st) {
	auto lmdUpdate = m_activeVisual.get().update(st, getPosition());

	// little hack, run it directly here ...
	// must be done in the SpriteVisual itself to work for statics too
	//lmdUpdate(m_activeVisual);

	return std::make_pair(static_cast<VisualBase *>(nullptr), lmdUpdate);
}

void Entity::setPositionHard(Vector2 vec) {
	getRigidBody()->SetTransform(b2Vec2(vec.x(), vec.y()), 0);
}
