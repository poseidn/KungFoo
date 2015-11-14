#include "EntityEngine.h"

#include <algorithm>
#include <cmath>
#include <vector>

#include "Entity.h"
#include "EntityTemplate.h"
#include "../RenderEngine.h"
#include "MoveAccessClass.h"
#include "../Timing.h"

#include "../Performance/SectionTimer.h"
#include "../Pathfinding/Node.h"

EntityEngine::EntityEngine() {
}

EntityEngine::~EntityEngine() {
}

// todo: make sure this index is cleaned up properly
void EntityEngine::addEntity(uniq<Entity> ent, std::string const& name, ManagedEntityList * managedList) {
	// add in index after a certain name
	m_entitiesIndex[name] = ent.get();
	addEntity(std::move(ent));
}

Entity * EntityEngine::getEntity(std::string const& name) {
	auto it = m_entitiesIndex.find(name);
	if (it == m_entitiesIndex.end()) {
		return nullptr;
	} else {
		return it->second;
	}

}

void EntityEngine::dropNavigationNodes(NodeVector & nodes) {
	nodes.clear();
}

bool EntityEngine::checkForCollisionObject(Vector2 const& position, const float radi) const {
	// check statics
	// this ensures that enemies keep their distance to walls and not get stuck
	const float posDelta = 3.0f;

	for (auto & sEnt : getStaticEntities()) {
		if (sEnt->doesCollide()) {
			// some easy criteria to be faster ( especially on the ouya )
			if ((std::abs(position.y() - sEnt->getPosition().y()) < posDelta)
					&& (std::abs(position.x() - sEnt->getPosition().x()) < posDelta)) {

				const Vector2 conAtoB = sEnt->getPosition() - position;
				const float conDist = conAtoB.magSquared();
				if (conDist < (radi + sEnt->getCollisionRadius())) {
					// that's a collision
					return true;
				}
			}
		}
	}
	return false;
}

void EntityEngine::generatePathfindingNodes(NodeVector & nodes) {
	// lay a grid over the static entities
	SectionTimer tm(GlobalTimingRepo::Rep, "EntityEngine.generatePathfindingNodes");

	const int resolutionFactor = 1;
	const float collisionMarginFactor = 2.5f;
	const float gridSize = 1.0f / float(resolutionFactor); // 0.5f;
	//const float neighbourDistance = sqrt(gridSize * gridSize * 2.0f) * 1.1f;

	float floatHighestY = 0;
	float floatLowestY = 100000000000.0f;
	for (auto & ent : getStaticEntities()) {
		floatHighestY = std::max(floatHighestY, ent->getPosition().y());
		floatLowestY = std::min(floatLowestY, ent->getPosition().y());
	}

	dropNavigationNodes(nodes);

	// protect against no entities
	if (getStaticEntities().size() == 0)
		return;

	assert(floatHighestY > floatLowestY);
	logging::Info() << "Generating navigation grid for lowY: " << floatLowestY << " highY: " << floatHighestY;

	const int highestY = int(std::ceil(floatHighestY));
	const int lowestY = int(std::floor(floatLowestY));
	const int spanY = highestY - lowestY;

	const float spanX = 15.0f;
	const int nodeCount = (spanX * resolutionFactor) * (spanY * resolutionFactor);

	nodes.resize(nodeCount);

	// with a resolution of 2 times the tile size
	const int sizeX = spanX * resolutionFactor;
	const int sizeY = (spanY * resolutionFactor);

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			Vector2 pos(float(x) * gridSize, float(y) * gridSize + float(lowestY));

			// do only add if there is no collision object near by
			if (!checkForCollisionObject(pos, gridSize * collisionMarginFactor)) {
				const int thisNodeLocation = sizeX * y + x;
				NodePtr n = &nodes[thisNodeLocation];
				n->Location = pos;

				// connect to left
				if (x > 0) {
					// left same line
					n->Neighbours.push_back(&nodes[thisNodeLocation - 1]);

					// left lower
					if (y > 0) {
						n->Neighbours.push_back(&nodes[thisNodeLocation - 1 - sizeX]);
					}
					// left upper
					if (y < (sizeY - 1)) {
						n->Neighbours.push_back(&nodes[thisNodeLocation - 1 + sizeX]);
					}
				}
				if (x < (sizeX - 1)) {
					// right same line
					n->Neighbours.push_back(&nodes[thisNodeLocation + 1]);
					// right lower
					if (y > 0) {
						n->Neighbours.push_back(&nodes[thisNodeLocation + 1 - sizeX]);
					}
					// right upper
					if (y < (sizeY - 1)) {
						n->Neighbours.push_back(&nodes[thisNodeLocation + 1 + sizeX]);
					}
				}

				if (y > 0) {
					// lower one
					n->Neighbours.push_back(&nodes[thisNodeLocation - sizeX]);
				}
				if (y < (sizeY - 1)) {
					// upper one
					n->Neighbours.push_back(&nodes[thisNodeLocation + sizeX]);
				}
			}
		}
	}
}

void EntityEngine::cleanManagedList(ManagedEntityList & managedList, Engines & e) {
	for (auto ent : managedList) {
		removeEntity(ent, e);
	}
}
/*
 void EntityEngine::cleanManagedStaticList(ManagedStaticEntityList & managedList, Engines & e) {
 for (auto ent : managedList) {
 removeStaticEntity(ent, e);
 }
 }*/

void EntityEngine::addStaticEntity(uniq<Entity> ent, ManagedStaticEntityList *managedList) {
//im_stat
// add partitioned in y
	auto itAddPosition = getStaticEntitiesRegionStart(
			EntityRegion(ent->getPosition().y(), ent->getPosition().y()));

// insert is before itAddPosition
	m_staticEntities.insert(itAddPosition, std::move(ent));
}

void EntityEngine::executeMoveIntents() {
	for (auto & et : getEntities()) {
		MoveAccessClass::applyMoveIntent(*et.get());
	}
}

void EntityEngine::updateDirtyEntities(ScreenTransform const& trans, VisualUpdatePairList & updateList) {
	for (auto & et : getEntities()) {
		if (et->isPositionDirty()) {
			updateList.push_back(et->updateVisual(trans));
			et->unsetPositionDirty();
		}
	}
}

EntityListUniq::iterator EntityEngine::getStaticEntitiesRegionStart(EntityRegion const& entRegion) {
	for (auto it = getStaticEntities().begin(); it != getStaticEntities().end(); it++) {
		if ((*it)->getPosition().y() > entRegion.m_lowerBound) {
			return it;
		}
	}
	return getStaticEntities().begin();
}

EntityListUniq::iterator EntityEngine::getStaticEntitiesRegionEnd(EntityRegion const& entRegion) {
	for (auto it = getStaticEntities().begin(); it != getStaticEntities().end(); it++) {
		if ((*it)->getPosition().y() > entRegion.m_upperBound) {
			return it;
		}
	}
	return getStaticEntities().end();
}

void EntityEngine::removeStaticEntity(EntityListUniq::iterator const& it, Engines & eg) {
// kill the visual

// TODO: memleak, remove this sprite visual in the corresponding unregister function
	(*it)->unregister(eg);
	/*	SpriteVisual * vis = (*it)->getActiveVisual();

	 if (vis != nullptr) {
	 re.removeSpriteVisual(vis);
	 }
	 */
	m_staticEntities.erase(it);
}

void EntityEngine::removeEntity(EntityListUniq::iterator const& it, Engines & e) {
	// find and erase from index list
	/*
	 auto itIndex = std::find(m_entitiesIndex.begin(), m_entitiesIndex.end(), it->get());

	 todo: this is a map and you have to find the value
	 use boost::multi_index ??

	 auto itIndex = m_entitiesIndex.find(it->get());
	 if ( itIndex != m_entitiesIndex.end) {
	 m_entitiesIndex.erase(itIndex);
	 }*/
	/*if ( itIndex != m_entitiesIndex.end()){
	 m_entitiesIndex.erase(itIndex);
	 }*/

	(*it)->unregister(e);
	getEntities().erase(it);
}

void EntityEngine::updatePathfinding() {
	generatePathfindingNodes(m_pathfindingNodes);
}

void EntityEngine::removeEntity(Entity * ent, Engines & e) {
	// find the pointer
	auto it = find_uniq(getEntities().begin(), getEntities().end(), ent);

	if (it == getEntities().end()) {
		logging::Fatal() << "Could not find entity to remove in entity list";
	} else {
		removeEntity(it, e);
	}
}

void EntityEngine::removeStaticEntity(Entity * ent, Engines & e) {
	// find the pointer
	auto it = find_uniq(getStaticEntities().begin(), getStaticEntities().end(), ent);

	if (it == getStaticEntities().end()) {
		logging::Fatal() << "Could not find static entity to remove in entity list";
	} else {
		removeStaticEntity(it, e);
	}
}

void EntityEngine::cleanAllStatic(Engines &eg) {
	while (getStaticEntities().begin() != getStaticEntities().end()) {
		removeStaticEntity(getStaticEntities().begin(), eg);
	}
	logging::Info() << "static entity count after kill: " << getStaticEntities().size();
}

void EntityEngine::cleanStaticBelow(const float yCoord, Engines &eg) {
	std::vector<Entity *> toRemove;

	for (auto it = getStaticEntities().begin(); it != getStaticEntities().end(); it++) {
		if ((*it)->getPosition().y() < yCoord) {
			toRemove.push_back(it->get());
		}
	}

	for (auto it : toRemove) {
		removeStaticEntity(it, eg);
	}
}

EntityTemplate const& EntityEngine::getTemplate(std::string const& name) const {
	auto it = m_templateMap.find(name);
	if (it == m_templateMap.end()) {
		logging::Fatal() << "Entitiy Template " << name << " not known";
	}

	return it->second;
}

EntityEngine::TemplateMap const& EntityEngine::getTemplateMap() const {
	return m_templateMap;
}

void EntityEngine::addTemplate(std::string const& name, EntityTemplate templ) {
	m_templateMap[name] = templ;
}

NodePtr EntityEngine::findClosestNode(Vector2 const& vec) {
	NodePtr minNode = nullptr;
	float minDist = 10000000.0f;

	for (auto & n : m_pathfindingNodes) {
		const float d = n.distanceTo(vec);
		if (d < minDist) {
			minNode = &n;
			minDist = d;
		}
	}

	return minNode;
}
