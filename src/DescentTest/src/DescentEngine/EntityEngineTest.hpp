#pragma once

#include <gtest/gtest.h>

#include <DescentEngine/src/EntityEngine/EntityEngine.h>

#include "Support/TestEntity.h"
#include <DescentEngine/src/EntityEngine/MoveAccessClass.h>

TEST(EntityEngine, cleanStaticEntities) {
	EntityEngine ng;

	auto testEnt1 = std14::make_unique<TestEntity>();
	auto testEnt2 = std14::make_unique<TestEntity>();

	MoveAccessClass::setPosition(*testEnt1, Vector2(0.0, 30.0));
	MoveAccessClass::setPosition(*testEnt2, Vector2(0.0, 3.0));

	ng.addStaticEntity(std::move(testEnt1));
	ng.addStaticEntity(std::move(testEnt2));

	ASSERT_EQ( size_t(2), ng.getStaticEntities().size());

	// has to have render engine now ..
	//ng.cleanStaticBelow(10.0);

	//ASSERT_EQ( size_t(1), ng.getStaticEntities().size());
	//ASSERT_EQ( 30.0, ng.getStaticEntities()[0].getPosition().y());

}

TEST(EntityEngine, moveEntities) {
	EntityEngine ng;

	auto testEnt1 = std14::make_unique<TestEntity>();
	auto testEnt2 = std14::make_unique<TestEntity>();

	auto testEnt1Ptr = testEnt1.get();
	auto testEnt2Ptr = testEnt2.get();

	MoveAccessClass::setPosition(*testEnt1, Vector2(0.0, 0.0));
	MoveAccessClass::setPosition(*testEnt2, Vector2(0.0, 3.0));

	ng.addEntity(std::move(testEnt1));
	ng.addEntity(std::move(testEnt2));
	ASSERT_EQ( size_t(2), ng.getEntities().size());

	ng.executeMoveIntents();

	ASSERT_EQ( testEnt1Ptr->getPosition(), Vector2(0.0, 0.0) );
	ASSERT_EQ( testEnt2Ptr->getPosition(), Vector2(0.0, 3.0) );

	testEnt1Ptr->deltaMoveIntent( Vector2(0.0, 5.0) );

	ASSERT_EQ( testEnt1Ptr->getPosition(), Vector2(0.0, 0.0) );
	ng.executeMoveIntents();
	ASSERT_EQ( testEnt1Ptr->getPosition(), Vector2(0.0, 5.0) );
	testEnt1Ptr->deltaMoveIntent( Vector2(10.0, 0.0) );
	ng.executeMoveIntents();
	ASSERT_EQ( testEnt1Ptr->getPosition(), Vector2(10.0, 5.0) );
}

