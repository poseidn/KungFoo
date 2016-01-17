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

#include <iostream>
#include <memory>

#include <gtest/gtest.h>

#include "Support/TestEntity.h"

#include <DescentEngine/src/EntityEngine/Entity.h>
#include <DescentEngine/src/Physics/PhysicsEngine.h>

TEST(Physics, startAndShutdown) {
	PhysicsEngine phyEg;
}

TEST(Physics, moveEntity) {
	PhysicsEngine phyEg;

	Vector2 initialPos(3.0f, 3.0f);
	Vector2 newPos(5.0f, 3.0f);

	Rectangle2 box(0.5f, 0.5f);
	auto ent = std::unique_ptr < TestEntity > (new TestEntity(initialPos, box));

	ent->setCollisionGroup(2);
	// collide with the floor and other from our collision group
	ent->setCollisionMask(CollisionGroups::Ground | 2);

	ent->setCollisionType(CollisionType::CircleDynamic);

	phyEg.registerEntity(ent.get());

	ent->setMoveIntent(newPos);

	// run for one second
	// dont make this time to big, as bullet can only subdivide in a certain part of substeps
	phyEg.step(0.1f);

	ASSERT_FLOAT_EQ(ent->getMoveIntent().x(), newPos.x());
	ASSERT_FLOAT_EQ(ent->getMoveIntent().y(), newPos.y());

	ASSERT_EQ(phyEg.getRegisteredEntitiesCount(), size_t(1));
}

TEST(Physics, collideEntity) {
	PhysicsEngine phyEg;

	Vector2 initialPos(3.0f, 3.0f);
	Vector2 newPos(3.0f, 5.0f);

	Rectangle2 box(0.5f, 0.5f);
	auto ent = std::unique_ptr < TestEntity > (new TestEntity(initialPos, box));
	ent->setCollisionGroup(2);
	// collide with the floor and other from our collision group
	ent->setCollisionMask(CollisionGroups::Ground | 2);

	ent->setCollisionType(CollisionType::CircleDynamic);
	phyEg.registerEntity(ent.get());
	ent->setMoveIntent(newPos);

	// box in between
	Rectangle2 boxCollide(5.0f, 0.5f);
	Vector2 wallPos(3.0f, 4.0f);
	auto entWall = std::unique_ptr < TestEntity > (new TestEntity(wallPos, boxCollide));
	entWall->setCollisionGroup(2);
	// collide with the floor and other from our collision group
	entWall->setCollisionMask(CollisionGroups::Ground | 2);

	entWall->setCollisionType(CollisionType::BoxStatic);
	phyEg.registerEntity(entWall.get());
	//entWall->setMoveIntent(newPos);

	// run for one second
	// dont make this time to big, as bullet can only subdivide in a certain part of substeps
	phyEg.step(0.1f);

	std::cout << "is at " << ent->getMoveIntent() << std::endl;

	ASSERT_TRUE(ent->getMoveIntent().y() < newPos.y());
}

TEST(Physics, collideEntityWithEntity) {
	PhysicsEngine phyEg;

	Vector2 initialPos(3.0f, 3.0f);
	Vector2 newPos(3.0f, 5.0f);

	Rectangle2 box(0.5f, 0.5f);
	auto ent = std::unique_ptr < TestEntity > (new TestEntity(initialPos, box));
	ent->setCollisionGroup(2);
	// collide with the floor and other from our collision group
	ent->setCollisionMask(CollisionGroups::Ground | 2);

	ent->setCollisionType(CollisionType::CircleDynamic);
	phyEg.registerEntity(ent.get());
	ent->setMoveIntent(newPos);

	// circle in between
	Rectangle2 circleCollide(1.0f, 1.0f);
	Vector2 wallPos(3.0f, 4.0f);
	auto entWall = std::unique_ptr < TestEntity > (new TestEntity(wallPos, circleCollide));
	entWall->setCollisionGroup(2);
	// collide with the floor and other from our collision group
	entWall->setCollisionMask(CollisionGroups::Ground | 2);

	entWall->setCollisionType(CollisionType::CircleDynamic);
	phyEg.registerEntity(entWall.get());
	//entWall->setMoveIntent(newPos);

	// run for one second
	// dont make this time to big, as bullet can only subdivide in a certain part of substeps
	phyEg.step(0.1f);
	std::cout << "is at " << ent->getMoveIntent() << std::endl;

	ASSERT_TRUE(ent->getMoveIntent().y() < newPos.y());
}

TEST(Physics, changeCollisionGroup) {
	PhysicsEngine phyEg;

	const Vector2 initialPos(3.0f, 3.0f);
	const Vector2 newPos(3.0f, 5.0f);

	Rectangle2 box(0.5f, 0.5f);
	auto ent = std::unique_ptr < TestEntity > (new TestEntity(initialPos, box));
	ent->setCollisionGroup(2);
	// collide with the floor and other from our collision group
	ent->setCollisionMask(CollisionGroups::Ground | 2);

	ent->setCollisionType(CollisionType::CircleDynamic);
	phyEg.registerEntity(ent.get());
	ent->setMoveIntent(newPos);

	// change collision settings after registering
	ent->setCollisionMask(0);

	// box in between
	Rectangle2 boxCollide(5.0f, 0.5f);
	Vector2 wallPos(3.0f, 4.0f);
	auto entWall = std::unique_ptr < TestEntity > (new TestEntity(wallPos, boxCollide));
	entWall->setCollisionGroup(2);
	// collide with the floor and other from our collision group
	entWall->setCollisionMask(CollisionGroups::Ground | 2);

	entWall->setCollisionType(CollisionType::BoxStatic);
	phyEg.registerEntity(entWall.get());

	phyEg.step(0.1f);

	std::cout << "is at " << ent->getMoveIntent() << std::endl;

	EXPECT_NEAR(ent->getMoveIntent().x(), newPos.x(), 0.001);
	EXPECT_NEAR(ent->getMoveIntent().y(), newPos.y(), 0.001);

}
