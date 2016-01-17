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

