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
