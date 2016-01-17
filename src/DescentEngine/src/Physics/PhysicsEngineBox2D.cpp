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

#include "PhysicsEngineBox2D.h"

#include <algorithm>
#include <array>

#include "../Util.h"

#include <Box2D/Box2D.h>

#include "../EntityEngine/Entity.h"

#include "CollisionGroups.h"

PhysicsEngineBox2D::PhysicsEngineBox2D() {

	m_b2world = std14::make_unique<b2World>(b2Vec2_zero);
}

PhysicsEngineBox2D::~PhysicsEngineBox2D() {
}

void PhysicsEngineBox2D::unregisterAllEntities() {
	for (auto & bd : m_bodiesAll) {
		m_b2world->DestroyBody(bd.RigidBody);
	}
	m_bodiesAll.clear();
	m_bodiesDynamic.clear();
}

void PhysicsEngineBox2D::unregisterEntity(Entity * ent, bool allowNotFound) {
	const bool isDynamic = (ent->getCollisionType() == CollisionType::CircleDynamic);

	auto lmbFindEntity = [ent] ( BodiesEntry & be ) {return be.RigidBody == ent->getRigidBody();};
	auto itRem = std::remove_if(m_bodiesAll.begin(), m_bodiesAll.end(), lmbFindEntity);
	if (itRem == m_bodiesAll.end()) {
		if (allowNotFound)
			return;
		else
			logging::Fatal() << "Physics Body not found";
	}
	m_bodiesAll.erase(itRem);

	if (isDynamic) {
		auto itRem = std::remove_if(m_bodiesDynamic.begin(), m_bodiesDynamic.end(), lmbFindEntity);
		if (itRem == m_bodiesDynamic.end()) {
			if (allowNotFound)
				return;
			else
				logging::Fatal() << "Physics Body not found";
		}
		m_bodiesDynamic.erase(itRem);
	}

	m_b2world->DestroyBody(ent->getRigidBody());
}

void PhysicsEngineBox2D::registerEntity(Entity * ent) {

	if (ent->getCollisionType() == CollisionType::NoCollideLike)
		return;

	const bool isDynamic = (ent->getCollisionType() == CollisionType::CircleDynamic);
	b2BodyDef newBody;
	newBody.position = b2Vec2(ent->getPosition().x(), ent->getPosition().y());
	newBody.userData = (void*) ent;

	if (isDynamic) {
		newBody.type = b2_dynamicBody;
	} else {
		newBody.type = b2_staticBody;
	}

	b2Body* dynamicBody = m_b2world->CreateBody(&newBody);
	dynamicBody->SetLinearDamping(ent->getDampingLinear());
	dynamicBody->SetAngularDamping(ent->getDampingLinear());

	b2PolygonShape polyShape;
	std::unique_ptr<b2Shape> * shape; // = nullptr;
	if (ent->getCollisionType() == CollisionType::BoxStatic) {
		const Rectangle2 rect = ent->getCollisionBox();
		// will use the double size internally, so half here
		polyShape.SetAsBox(rect.width() * 0.5f, rect.height() * 0.5f);
	} else if (ent->getCollisionType() == CollisionType::CircleDynamic) {

		// make not a circle but a box with round edges
		// this makes the gameplay nicer when running into enemies
		const float rad = ent->getCollisionRadius();
		const float displacedFract = rad * 0.84f;
		std::array<b2Vec2, 8> vertices;

		// this goes CCW
		// top
		vertices[0].Set(displacedFract, rad);
		vertices[1].Set(-displacedFract, rad);

		// left
		vertices[2].Set(-rad, displacedFract);
		vertices[3].Set(-rad, -displacedFract);

		// bottom
		vertices[4].Set(-displacedFract, -rad);
		vertices[5].Set(displacedFract, -rad);

		// right
		vertices[6].Set(rad, -displacedFract);
		vertices[7].Set(rad, displacedFract);

		polyShape.Set(vertices.data(), vertices.size());
	}

	b2FixtureDef def;
	def.shape = &polyShape;
	def.density = ent->getMass();
	setFilterData(def.filter, ent);

	dynamicBody->CreateFixture(&def);

	float limitedLifetime = -1.0f;
	if (ent->hasLimitedPhysicsLifetime()) {
		limitedLifetime = ent->getLimitedPhysicsLifetime();
	}

	ent->setRigidBody(dynamicBody);

	m_bodiesAll.emplace_back(BodiesEntry(dynamicBody, limitedLifetime));

	if (isDynamic) {
		m_bodiesDynamic.emplace_back(BodiesEntry(dynamicBody, limitedLifetime));
	}
}

void PhysicsEngineBox2D::step(float dt) {

	const int32 velocityIterations = 10;
	const int32 positionIterations = 8;

	std::vector<Entity *> toRemove;

// move dynamic entities to their new positions
	for (BodiesEntry & bd : m_bodiesDynamic) {

		Entity * ent = static_cast<Entity *>(bd.RigidBody->GetUserData());

		// has this entity to be disabled ?
		if (bd.LimitedLifetime) {
			bd.PhysicsLifetime -= dt;

			if (bd.PhysicsLifetime < 0.0f) {
				// lifetime is over, remove from simulation as soon as possible
				toRemove.push_back(ent);
				continue;
			}
		}

		// need to disable collisions for some ?
		b2Filter filterData = bd.RigidBody->GetFixtureList()->GetFilterData();
		if ((ent->collisionGroup() != filterData.categoryBits) || (ent->collisionMask() != filterData.maskBits)
		/*|| ent->isSkipCollsionOneRound() */) {
			setFilterData(filterData, ent);
			bd.RigidBody->GetFixtureList()->SetFilterData(filterData);
		}

		// reset angular velocity for all dynamics, to prevent build-up
		bd.RigidBody->SetAngularVelocity(0.0f);

		if (ent->hasInitialVelocity()) {
			if (!ent->m_initialVelocitySet) {
				bd.RigidBody->SetLinearVelocity(
						b2Vec2(ent->retrieveInitialVelocity().x(), ent->retrieveInitialVelocity().y()));
				ent->m_initialVelocitySet = false;
			}
			continue;
		}

		const Vector2 con = ent->getMoveDelta();
		const float speed = con.mag() / dt;

		if (speed > 0.01f) {
			const Vector2 dir = con.normalizedCopy();

			bd.RigidBody->SetLinearVelocity(b2Vec2(dir.x() * speed, dir.y() * speed));
		} else {
			bd.RigidBody->SetLinearVelocity(b2Vec2_zero);
		}
	}

	for (Entity * ent : toRemove) {
		unregisterEntity(ent);
	}

// use a fixed timestep value here, otherwhise box2d stutters
	m_b2world->Step(dt, velocityIterations, positionIterations);
	m_b2world->ClearForces();

	const float nearZero = 0.001f;

	for (auto & bd : m_bodiesDynamic) {
		Entity * ent = static_cast<Entity *>(bd.RigidBody->GetUserData());
		b2Transform trans = bd.RigidBody->GetTransform();
		ent->setPosition(Vector2(trans.p.x, trans.p.y));
	}
}

size_t PhysicsEngineBox2D::getRegisteredEntitiesCount() const {
	return m_bodiesAll.size();
}

size_t PhysicsEngineBox2D::getRegisteredDynamicsEntitiesCount() const {
	return m_bodiesDynamic.size();
}

