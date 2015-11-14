#pragma once

#include <DescentEngine/src/EntityEngine/Entity.h>

#include "TestEntity.h"
/*
 class TestEntity: Entity {
 public:
 TestEntity : Entity( Vector2::Zero(), Rectangle2::Unit() )
 {

 }

 };*/

class TestGameState {
public:
	void addStaticEntity(Entity * ent) {

	}
};

class TestEntityFactory {
public:

	typedef std::tuple<Vector2, bool> NonVisualItem;

	template<class TEntityType>
	uniq<TEntityType> create(TexturePtr tex, Vector2 initialPosition, Rectangle2 boundingBox, LayerPriority prio =
			LayerPriorityBottom, float animTiming = 0.05f) {
		return TestEntity::createDummy();

	}

	template<class TEntityType>
	uniq<TEntityType> createNonVisual(Vector2 initialPosition, Rectangle2 boundingBox, LayerPriority prio =
			LayerPriorityBottom, bool noCollisionJump = false) {
		createdNonVisual.push_back(NonVisualItem(initialPosition, noCollisionJump));
		return (TEntityType *) TestEntity::createDummy();
	}

	template<class TEntityType>
	uniq<TEntityType> createMultiVisual(TextureSet & tex, Vector2 initialPosition, Rectangle2 boundingBox,
			Rectangle2 visualSize, LayerPriority prio = LayerPriorityBottom) {
		return TestEntity::createDummy();
	}

// todo: refactor these two methods
	template<class TEntityTemplate, class TEntityType>
	uniq<TEntityType> create(std::string const& templateName, Vector2 initialPosition, LayerPriority prio =
			LayerPriorityBottom) {
		createdTemplates.push_back(templateName);
		// todo: might end bad, because we promote to a type which we dont actually have ..
		return (TEntityType *) TestEntity::createDummy();
	}

	template<class TEntityTemplate, class TEntityType>
	uniq<TEntityType> createMultiVisual(std::string const& templateName, Vector2 initialPosition,
			LayerPriority prio = LayerPriorityBottom) {
		createdTemplates.push_back(templateName);
		return TestEntity::createDummy();
	}

	std::vector<std::string> createdTemplates;
	std::vector<NonVisualItem> createdNonVisual;
};
