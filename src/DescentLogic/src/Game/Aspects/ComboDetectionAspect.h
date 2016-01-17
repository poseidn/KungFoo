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

#include <random>
#include <map>
#include <array>
#include <tuple>
#include <vector>
#include <stack>
#include <functional>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/math/constants/constants.hpp>
#include <DescentEngine/src/Cpp11.h>

#include <DescentEngine/src/VectorTypes.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentEngine/src/DataTypes/RingBuffer.h>

#include "../GameState.h"

class ComboDetectionAspect CPP11_FINAL : public Aspect<GameState> {
public:

	ComboDetectionAspect() {
	}

	virtual ~ComboDetectionAspect() {
	}

// holds an input pattern that will be compared to the player input

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	class Kill {
	public:
		Kill() :
				UsedForCombo(0) {
		}

		Kill(float ds) :
				Timestamp(ds), UsedForCombo(0) {
		}
		float Timestamp;
		int UsedForCombo;

	};

	//static constexpr size_t RingBufferSize = 15;
	typedef RingBuffer<Kill, 15> KillBuffer;

	class PlayerKills {
	public:
		KillBuffer Kills;
	};

	std::map<PlayerId, PlayerKills> m_kills;

	void analyze(GameState & gs);
	bool bufferEntriesUnused(KillBuffer const& buffer, int bit, int start, int end);
	void markEntriesUsed(KillBuffer & buffer, int bit, int start, int end);

};

