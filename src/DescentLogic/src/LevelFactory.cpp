#include "LevelFactory.h"

#include <algorithm>
#include <tinyxml2.h>

#include <DescentEngine/src/Visuals/LightVisual.h>
#include <DescentEngine/src/EntityEngine/EntityFactory.h>
#include <DescentEngine/src/RandomEngine.h>
#include <DescentEngine/src/Rectangle.h>
#include <DescentEngine/src/Timing.h>

#include <DescentLogic/src/Entities/EnemyEntity.h>

#include <DescentLogic/src/Entities/TextureIds.h>

void LevelLoader::loadFragment(std::string const& json, LevelFragment & frag) {

	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError res = xmlDoc.Parse(json.c_str(), json.size());
	if (res != tinyxml2::XML_NO_ERROR) {
		logging::Error() << "cant parse xml";
		throw LevelParsingException();
	}

	tinyxml2::XMLElement * rootElem = xmlDoc.FirstChildElement("LevelFragment");
	assert(rootElem);

	const std::string conIn = rootElem->Attribute("connectIn");
	const std::string conOut = rootElem->Attribute("connectOut");

	frag.Size = XmlTools::readVector2(rootElem, "size", Vector2(1, 1));
	frag.ConnectionsIn = XmlTools::parseStringList(conIn);
	frag.ConnectionsOut = XmlTools::parseStringList(conOut);

	for (tinyxml2::XMLElement * tileElem = rootElem->FirstChildElement("Tile"); tileElem != nullptr; tileElem =
			tileElem->NextSiblingElement("Tile")) {
		//const Vector2 repeat = XmlTools::readVector2(tileElem, "repeat", Vector2(1, 1));
		const Vector2 center = XmlTools::readVector2(tileElem, "center", Vector2(1, 1));
		const Vector2 repeat = XmlTools::readVector2(tileElem, "repeat", Vector2(1, 1));
		const int collides = XmlTools::readInt(tileElem, "collides", 0);
		const int collidesInJump = XmlTools::readInt(tileElem, "collidesInJump", 1);
		const std::string entity = XmlTools::readString(tileElem, "entity");
		const std::string entityType = XmlTools::readString(tileElem, "type");

		frag.Tiles.emplace_back(
				LevelTile(center, repeat, collides == 1, entityType, entity, collidesInJump == 1));
	}
}

void LevelFactory::reset() {
	m_lastFragment = nullptr;
	m_currentLayer = 0;
}

void LevelFactory::collisionTestLevel(GameState & gs) {

	// collision works best, when the wall are connected, but don't cross into each other !
	/*	WallCollisionEntity * col = EntityFactory::createNonVisual<WallCollisionEntity>(m_engines,
	 Vector2(8.0, 2.0), Rectangle2(16.0, 1.0));
	 gs.addStaticEntity(col);

	 col = EntityFactory::createNonVisual<WallCollisionEntity>(m_engines, Vector2(15.0, 8.0),
	 Rectangle2(1.0, 11.0));
	 gs.addStaticEntity(col);

	 col = EntityFactory::createNonVisual<WallCollisionEntity>(m_engines, Vector2(8.0, 8.0),
	 Rectangle2(1.0, 3.0));
	 gs.addStaticEntity(col);

	 col = EntityFactory::createNonVisual<WallCollisionEntity>(m_engines, Vector2(4.0, 13.0),
	 Rectangle2(4.0, 4.0));
	 gs.addStaticEntity(col);*/
}

bool LevelFactory::canConnect(LevelFragment const& prevFrag, LevelFragment const& nextFrag) const {
	for (auto const& type : prevFrag.ConnectionsOut) {
		for (auto const& typeOut : nextFrag.ConnectionsIn) {
			if (type == typeOut)
				return true;
		}
	}
	return false;
}

void LevelFactory::renderTestLevel(GameState & gs) {

	//typedef WallEntity wall_type;
	Entity * ent;

	// depends on the order of how they are registereted on android. buhhh
	/*	ent = EntityFactory::create<  wall_type>(m_engines, "wall_side", Vector2(4.0f, 4.0f));
	 gs.addStaticEntity(ent);
	 ent = EntityFactory::create<  wall_type>(m_engines, "floor_wood", Vector2(4.0f, 4.0f));
	 gs.addStaticEntity(ent);*/
	/*
	 ent = EntityFactory::create<  wall_type>(m_engines, "floor_wood", Vector2(4.0f, 14.0f));
	 gs.addStaticEntity(ent);*/

	return;
}

void LevelFactory::loadFragment(GameState & gs, std::string const& fragName) {
	EntityFactory fact(gs.getEngines());
	LevelLoader loader;

	std::vector<LevelFragment const*> possibleFragments;

	auto it = std::find_if(m_fragments.begin(), m_fragments.end(),
			[ fragName] ( LevelFragment const& c) -> bool {
				return (c.Name == fragName);
			});

	if (it == m_fragments.end()) {
		logging::Fatal() << "Level fragment with name " << fragName << " not found";
	}

	loader.applyFragment(*it, gs, fact, m_currentLayer);

	logging::Info() << "Level fragment " << fragName << " complete";
}

void LevelFactory::nextLayers(GameState & gs, unsigned int amount) {
	// one additional enemy per 100 layers
	const int lowerEnemyCount = 1;

	if (int(amount) > (int(m_currentLayer) - 20)) {
		Timing timeStreaming;

		LevelLoader loader;
		EntityFactory fact(gs.getEngines());

		std::vector<LevelFragment const*> possibleFragments;

		// because currentLayer will be increased once the fragment has been added
		const int thisLayer = m_currentLayer;

		if (m_lastFragment) {
			//logging::Info() << "Last Fragment " << m_lastFragment->Name;
		}

		for (LevelFragment const& frag : m_fragments) {

			if (m_lastFragment != nullptr) {
				//logging::Info() << "Checking Fragment " << frag.Name;

				if (canConnect(*m_lastFragment, frag)) {
					//logging::Info() << "-> can connect" << frag.Name;
					possibleFragments.push_back(&frag);
				} else {
					//logging::Info() << "-> can't connect" << frag.Name;
				}
			} else {
				possibleFragments.push_back(&frag);
			}
		}

		const int pick = gs.getEngines().randomEngine().randomInt(
				RandomEngine::SpanInt(0, possibleFragments.size() - 1));

		//logging::Info() << "--> picked fragment " << pick << " : " << possibleFragments[pick]->Name;

		LevelFragment const* frag = possibleFragments[pick];
		m_lastFragment = frag;

		loader.applyFragment(*frag, gs, fact, m_currentLayer);
		m_currentLayer += frag->Size.y();

		// bring a new enemy every five layers
		const int enemyAdd = std::floor(float(thisLayer) / 30.0f);
		// the lower enemy count must increase, too
		// otherwise, the mean will stay in a quite 'easy' region
		const int enemyCount = gs.getEngines().randomEngine().randomInt(
				RandomEngine::SpanInt(lowerEnemyCount + enemyAdd, lowerEnemyCount + 2 * enemyAdd));
		// max one per new layer !
		const int enemyCountFat = gs.getEngines().randomEngine().randomInt(RandomEngine::SpanInt(0, 1)) == 0;

		const float maxPlacementRadius = 5.0f;
		const float enemyCollisionRadius = 0.7f;
		const float enemyFatCollisionRadius = 0.7f;

		for (int i = 0; i < enemyCount; i++) {
			addEnemy < EnemyEntity
					> ("enemy1", enemyCollisionRadius, maxPlacementRadius, frag, thisLayer, gs, fact);
		}
		for (int i = 0; i < enemyCountFat; i++) {
			addEnemy < EnemyFatEntity
					> ("enemy2", enemyFatCollisionRadius, maxPlacementRadius, frag, thisLayer, gs, fact);

		}

		// update pathfinding
		gs.getEngines().entityEngine().updatePathfinding();

		const float dsStreaming = timeStreaming.end();
		logging::Info() << "Streaming next level fragment took " << dsStreaming << " seconds";
	}
}

