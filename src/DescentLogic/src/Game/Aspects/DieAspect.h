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
