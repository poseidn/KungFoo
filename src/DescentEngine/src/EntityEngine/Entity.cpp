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
