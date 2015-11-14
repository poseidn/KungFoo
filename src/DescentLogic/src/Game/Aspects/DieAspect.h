#pragma once

#include <map>
#include <array>

#include <DescentEngine/src/VectorTypes.h>
#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentEngine/src/SoundEngine/PlayHandle.h>
#include "../PlayerData.h"

class GameState;
class SingleVisualEntity;

class DieAspect CPP11_FINAL : public Aspect<GameState> {
public:
	DieAspect() {
	}

	virtual ~DieAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

	void step(GameState & gs, float deltaT);

private:

	void stopSiren(GameState & gs);
	void playerDied(GameState & gs, PlayerData & pd);
	void gotoGameOver(GameState & gs);
	void playerRespawn(GameState & gs, PlayerData & pd);

	void updateMarker(PlayerData & pd, bool belowHorizon, Vector3 const& camLocation);

	class DeathInfo {
	public:
		DeathInfo() :
				TimeDead(-1.0f) {
		}

		float TimeDead;

	};

	std::map<PlayerId, DeathInfo> m_deathInfo;

	// todo: fix this for multiple players
	PlayHandle m_dieWarningSound;
	std::array<SingleVisualEntity *, 4> m_marker;
};
