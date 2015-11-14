#pragma once

#include <list>

#include <boost/noncopyable.hpp>

#include <DescentEngine/src/Signals.h>
#include <DescentEngine/src/Engines.h>
#include <DescentEngine/src/StateEngine/StateBase.h>

#include "PlayerData.h"
#include "../Config/GameRules.h"

class Entity;
class PlayerEntity;
class BloodEntity;
class EnemyEntity;
class FighterEntity;
class InputContainer;
class LevelFactory;

enum class GameMode {
	Coop
};

enum class ComboType {
	// combo done by one player alone
	Solo,
	// combo achieved by more than one player
	Coop
};

class GameState: public StateBase {
public:
	typedef std::list<EnemyEntity *> EnemyList;
	typedef std::list<BloodEntity *> FragmentList;

	GameState(Engines & eg);

	slots::Slot<GameState &, StateChangeInfoPtr const&> slotActivateState;
	slots::Slot<GameState &> slotDeactivateState;

	slots::Slot<GameState &, float> slotStep;

	// delta move the player to a new location
	// this can be called by the various input devices
	slots::Slot<GameState &, Vector2 const&, PlayerId> slotPlayerMove;
	slots::Slot<GameState &, PlayerId> slotPlayerJump;
	slots::Slot<GameState &, PlayerId> slotPlayerKick;
	slots::Slot<GameState &, PlayerId> slotPlayerSpecialMove;

	slots::Slot<GameState &, PlayerId,
	// enemies kill for combo
			int,
			// points for combo
			int, ComboType> slotComboDone;

	slots::Slot<GameState &> slotOpenMenu;

	slots::Slot<GameState &, Entity *> slotEntityAdded;
	slots::Slot<GameState &, PlayerId, EnemyEntity *> slotEnemyDied;

	slots::Slot<GameState &, PlayerId, size_t, size_t> slotScoreIncrease;

	slots::Slot<GameState &, bool> slotDebugSwitchScrolling;
	slots::Slot<GameState &, bool> slotDebugSwitchRenderTiles;

	virtual void onActivateState(StateChangeInfoPtr const& changeInfo) CPP11_OVERRIDE {
		slotActivateState.signal(*this, changeInfo);
	}

	virtual void onDeactivateState() CPP11_OVERRIDE {
		slotDeactivateState.signal(*this);
	}

	void setPlayerEntity(PlayerId id, PlayerEntity * e) {
		m_playerData[id].Entity = e;
	}

	GameMode getGameMode() const {
		return GameMode::Coop;
	}

	PlayerEntity * getPlayerEntity(PlayerId id) const {
		return m_playerData[id].Entity;
	}

	EnemyList & getEnemies() {
		return m_enemies;
	}

	FragmentList & getFragemts() {
		return m_fragments;
	}

	Engines & getEngines() {
		return m_engines;
	}

	int getTotalScore(PlayerId id) const {
		return m_playerData[id].TotalScore;
	}

	void increaseScore(PlayerId id, int by) {
		m_playerData[id].TotalScore += by;
		updateScoreDisplay();
		slotScoreIncrease.signal(*this, id, m_playerData[id].TotalScore - by, m_playerData[id].TotalScore);
	}

	void increaseScoreAllPlayers(int by) {

		for (PlayerData & pd : getPlayers()) {
			pd.TotalScore += by;
			slotScoreIncrease.signal(*this, pd.Id, pd.TotalScore - by, pd.TotalScore);
		}
		updateScoreDisplay();
	}

	void updateScoreDisplay();

	void addEnemyEntity(uniq<EnemyEntity> entEnemy);

	void addFragment(uniq<BloodEntity> frag);

	void removeEnemyEntity(EnemyEntity * entEnemy);

	void addEntity(uniq<Entity> ent);
	// will also index the entity for fast lock-up using the string
	void addEntity(uniq<Entity> ent, std::string const& name);

	void addStaticEntity(uniq<Entity> ent);

	std::vector<PlayerData> & getPlayers() {
		return m_playerData;
	}

	std::vector<PlayerData> const& getPlayers() const {
		return m_playerData;
	}

	int getTotalScorePlayerSum() const;

	void clearAllStaticEntities();

	void loadTestFragment();


	void logSignalPerformance() const;

	LevelFactory * getLevelFactory() const {
		return m_factory.get();
	}

	void setPlayerCount(int count);

	size_t getPlayerCount() const {
		return m_playerData.size();
	}

	void reset();

	float getTimestamp() const {
		return m_timestamp;
	}

	TextVisual * getTextScore() {
		return m_textScore;
	}

	void setTextScore(TextVisual * v) {
		m_textScore = v;
	}

	virtual std::string getDebugState() const CPP11_OVERRIDE {
		std::stringstream sState;

		sState << " -- Game State -- " << std::endl;
		sState << " --> Enemies : " << m_enemies.size() << std::endl;
		return sState.str();
	}

	float getDelayedScrolling() const {
		return m_delayedScrolling;
	}

	void setDelayedScrolling(float sc) {
		m_delayedScrolling = sc;
	}

	bool getScrollActive() const {
		return m_scrollActive;
	}

	void setScrollActive(bool act = true) {
		m_scrollActive = act;
	}

	std::string m_levelName;

private:

	TextVisual * m_textScore;

	float m_timestamp;

	std::vector<PlayerData> m_playerData;

	Engines & m_engines;
	EnemyList m_enemies;

	FragmentList m_fragments;

	std::unique_ptr<LevelFactory> m_factory;

	float m_delayedScrolling = GameRules::DelayedScrolling;
	bool m_scrollActive = false;
}
;

