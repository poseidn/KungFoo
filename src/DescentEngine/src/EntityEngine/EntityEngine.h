#pragma once

#include "../Cpp11.h"
#include "Entity.h"
#include "EntityList.h"
#include "EntityTemplate.h"
#include "../Pathfinding/Pathfinding.h"
#include "../Visuals/DeferredVisualUpdate.h"

#include <vector>
#include <memory>
#include <unordered_map>

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

class ScreenTransform;

class Engines;
class EntityTemplate;
class RenderEngine;
class VisualBase;

class EntityRegion: boost::noncopyable {
public:
	EntityRegion(float lowerBound, float upperBound) :
			m_lowerBound(lowerBound), m_upperBound(upperBound) {

	}

	const float m_lowerBound;
	const float m_upperBound;
};

// todo: segment to swap in out values and have faster access
class EntityEngine CPP11_FINAL : boost::noncopyable {
public:

	typedef std::list<VisualUpdatePair> VisualUpdatePairList;

	// necessary due to the size_of issue of the ptr_vector
	EntityEngine();
	~EntityEngine();

	EntityListUniq::iterator getStaticEntitiesRegionStart(EntityRegion const& entRegion);

	EntityListUniq::iterator getStaticEntitiesRegionEnd(EntityRegion const& entRegion);

	//void addEntity(Entity * ent, ManagedEntityList * managedList = nullptr);
	void addEntity( uniq< Entity > ent, ManagedEntityList * managedList = nullptr) {
		if (managedList) {
			managedList->push_back(ent.get());
		}
		m_entities.push_back( std::move(ent) );
	}

	// will also index the entity for fast lock-up using the string
	void addEntity(uniq< Entity> ent, std::string const& name, ManagedEntityList * managedList = nullptr);

	// will never move
	void addStaticEntity(uniq<Entity> ent, ManagedStaticEntityList *managedList = nullptr);

	void updatePathfinding();

	EntityListUniq const& getEntities() const {
		return m_entities;
	}

	/*EntityList & getEntities() {
	 return m_entities;
	 }*/

	EntityListUniq & getEntities() {
		return m_entities;
	}

	NodePtr findClosestNode(Vector2 const& vec);

	Entity * getEntity(std::string const& name);

	EntityListUniq & getStaticEntities() {
		return m_staticEntities;
	}

	EntityListUniq const& getStaticEntities() const {
		return m_staticEntities;
	}

	void removeStaticEntity(EntityListUniq::iterator const& it, Engines & re);
	void removeStaticEntity(Entity * ent, Engines & e);

	void removeEntity(EntityListUniq::iterator const& it, Engines & e);
	void removeEntity(Entity * ent, Engines & e);

	void executeMoveIntents();

	void updateDirtyEntities(ScreenTransform const& trans, VisualUpdatePairList & updateList);

	void cleanStaticBelow(const float yCoord, Engines & eg);

	// todo: check for mem leaks after this call
	void cleanAllStatic(Engines & eg);

	void cleanManagedList(ManagedEntityList & managedList, Engines & e);
	//void cleanManagedStaticList(ManagedStaticEntityList &managedList, Engines & e);

	NodeVector & getPathfindingNodes() {
		return m_pathfindingNodes;
	}

	// is reused by alle fighte entities so the lists etc. only need be allocated once
	Pathfinding & getPathfinding() {
		return m_pathfinding;
	}

	typedef std::unordered_map<std::string, EntityTemplate> TemplateMap;

	// may support polymorphism of the EntityTemplate class at some point
	EntityTemplate const& getTemplate(std::string const& name) const;
	TemplateMap const& getTemplateMap() const;

	void addTemplate(std::string const& name, EntityTemplate templ);
	//void addTemplateUniq(std::string const& name, uniq<EntityTemplate> templ);

private:
	void dropNavigationNodes(NodeVector & nodes);
	void generatePathfindingNodes(NodeVector & nodes);
	bool checkForCollisionObject(Vector2 const& position, const float radi) const;

	NodeVector m_pathfindingNodes;

	EntityListUniq m_entities;
	EntityListUniq m_staticEntities;
	EntityIndex m_entitiesIndex;

	Pathfinding m_pathfinding;

	TemplateMap m_templateMap;
	std::unordered_map<std::string, uniq<EntityTemplate>> m_templateMapUniq;
};

