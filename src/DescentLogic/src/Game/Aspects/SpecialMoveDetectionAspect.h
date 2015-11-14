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

