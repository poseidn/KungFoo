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

#include <DescentEngine/src/EntityEngine/EntityEngine.h>

#include <DescentEngine/src/EntityEngine/Entity.h>

class TestEntity: public Entity {
public:
	TestEntity() :
			Entity(Vector2::Zero(), Rectangle2::Unit()) {
	}

	TestEntity(Vector2 const & pos, Rectangle2 const & box) :
			Entity(pos, box) {
	}

	virtual ~TestEntity() {
	}

	static uniq<Entity> createDummy() {
		return std14::make_unique<TestEntity>();
	}


	virtual void unregister(Engines & eg) CPP11_OVERRIDE {
	}

	virtual CollisionType getCollisionType() const CPP11_OVERRIDE {
		return m_colType;
	}

	void setCollisionType(CollisionType tp) {
		m_colType = tp;
	}

	CollisionType m_colType;
};
/*
 class TestEntityMover: public MoveAccessClass
 {
 public:
 static void setPosition(Entity & ent, Vector2 const& pos)
 {
 ent.setPosition(pos);
 }
 };
 */
