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
