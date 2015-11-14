#pragma once

#include <random>
#include <map>

// to have uint32_t in Visual Studio
#include <cstdint>

#include <DescentEngine/src/VectorTypes.h>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include <DescentLogic/src/Game/PlayerData.h>

class GameState;

class MovePlayerAspect: public Aspect<GameState> {
public:
	MovePlayerAspect(bool scrollEnabled) :
			m_scrollEnabled(scrollEnabled), m_randDist(1, 3) {
	}

	virtual ~MovePlayerAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:

	void switchScrolling(GameState & gs, bool enabled);

	void step(GameState & gs, const float deltaT);
	void playerMove(GameState & gs, Vector2 const& vec, PlayerId id);
	void playerJump(GameState & gs, PlayerId id);
	void playerKick(GameState & gs, PlayerId id);
	void playerBiking(GameState & gs, PlayerId id);

	float computeMovementDecay(const float maxSpeed, const float resSpeed);

	class Movements {
	public:
		Movements() :
				m_stepMovement(0, 0), m_residualMovement(0, 0), m_jumpInit(false), m_kickInit(false), m_bikingInit(
						false), m_kickCount(0) {
		}

		Vector2 m_stepMovement;
		Vector2 m_residualMovement;

		bool m_jumpInit;
		bool m_kickInit;
		bool m_bikingInit;

		size_t m_kickCount;
	};

	bool m_scrollEnabled;

	std::map<PlayerId, Movements> m_movements;

	// culmulated movement intended during one step

	// todo: use global rand engine here
	std::uniform_int_distribution<uint32_t> m_randDist;
	std::mt19937 m_randEngine;
};
