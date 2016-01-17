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

#include <DescentEngine/src/VectorTypes.h>
#include <DescentEngine/src/Log.h>
//#include <DescentEngine/src/Input/InputContainer.h>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include <DescentEngine/src/DataTypes/RingBuffer.h>

#include "SpecialMoves/PatternNodes.h"
#include "SpecialMoves/InputItem.h"
#include "SpecialMoves/InputPattern.h"
#include "SpecialMoves/Reporter.h"

#include "../GameState.h"

using namespace special_move;

class SpecialMoveDetectionAspect: public Aspect<GameState> {
public:

	virtual ~SpecialMoveDetectionAspect() = default;
// holds an input pattern that will be compared to the player input

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:

	class PlayerReport {
	public:

		Reporter<KeyPressReport> m_jumpKeyReport;
		Reporter<KeyPressReport> m_kickKeyReport;

		Reporter<DirectionReport> m_rightDirectionReport;
		Reporter<DirectionReport> m_leftDirectionReport;
		Reporter<DirectionReport> m_upDirectionReport;
		Reporter<DirectionReport> m_downDirectionReport;
	};

	void initReport(PlayerReport & rep);
	std::map<PlayerId, PlayerReport> m_reports;
	std::vector<InputPattern> m_patterns;

	void step(GameState & gs, const float deltaT);
	void analyzeRingBuffer(GameState &, InputRecordType &, PlayerId id);

	InputItem extractInputItem(GameState & gs, PlayerReport & rep, PlayerId id);

	class PlayerInput {
	public:
		InputRecordType m_inputRecord;
		InputItem m_activeInputItem;
	};

	std::map<PlayerId, PlayerInput> m_inputs;
};

