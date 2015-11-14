#pragma once

#include <gtest/gtest.h>

#include <DescentLogic/src/Game/Aspects/SpecialMoveDetectionAspect.h>

using itemNS = special_move::InputItem;
using specialNS = SpecialMoveDetectionAspect;

TEST(SpecialMoveDetectionAspect, InputItemCompare) {
	special_move::InputItem iiA(itemNS::KeyPressEnum::KeyA);
	special_move::InputItem iiB(itemNS::KeyPressEnum::KeyB);

	ASSERT_FALSE(iiA == iiB);
	ASSERT_TRUE(iiA != iiB);

	ASSERT_FALSE(iiA != iiA);
	ASSERT_TRUE(iiA == iiA);

}

TEST(SpecialMoveDetectionAspect, SingleNode) {
	special_move::SingleNode node((special_move::InputItem(itemNS::KeyPressEnum::KeyB)));

	special_move::InputRecordType recordFullMatch;
	special_move::Deactivator deacFullMatch(recordFullMatch);

	recordFullMatch.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordFullMatch.push(special_move::InputItem(itemNS::DirectionEnum::Up));
	recordFullMatch.push(special_move::InputItem(itemNS::KeyPressEnum::KeyB));
	recordFullMatch.push(special_move::InputItem(itemNS::KeyPressEnum::KeyA));

	special_move::InputRecordType recordNoMatch;
	special_move::Deactivator deacNoMatch(recordNoMatch);

	recordNoMatch.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordNoMatch.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordNoMatch.push(special_move::InputItem(itemNS::KeyPressEnum::Undefined));
	recordNoMatch.push(special_move::InputItem(itemNS::DirectionEnum::Up));
	recordNoMatch.push(special_move::InputItem(itemNS::KeyPressEnum::KeyA));

	auto matchResTrue = node.match(recordFullMatch, deacFullMatch);
	auto matchResFalse = node.match(recordNoMatch, deacNoMatch);

	ASSERT_TRUE(std::get < 0 > (matchResTrue));
	ASSERT_EQ(std::get < 1 > (matchResTrue), -1);
	ASSERT_EQ(std::get < 2 > (matchResTrue), -1);

	ASSERT_FALSE(std::get < 0 > (matchResFalse));

}

TEST(SpecialMoveDetectionAspect, ConjuctionNode) {
	special_move::ConjuctionNode node((special_move::InputItem(itemNS::KeyPressEnum::KeyB)),
			(special_move::InputItem(itemNS::KeyPressEnum::KeyA)));

	special_move::InputRecordType recordFullMatch;
	special_move::Deactivator deacFullMatch(recordFullMatch);

	recordFullMatch.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordFullMatch.push(special_move::InputItem(itemNS::KeyPressEnum::KeyB));
	recordFullMatch.push(special_move::InputItem(itemNS::DirectionEnum::Up));
	recordFullMatch.push(special_move::InputItem(itemNS::KeyPressEnum::KeyA));

	special_move::InputRecordType recordNoMatch;
	special_move::Deactivator deacNoMatch(recordNoMatch);

	recordNoMatch.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordNoMatch.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordNoMatch.push(special_move::InputItem(itemNS::KeyPressEnum::Undefined));
	recordNoMatch.push(special_move::InputItem(itemNS::DirectionEnum::Up));
	recordNoMatch.push(special_move::InputItem(itemNS::KeyPressEnum::KeyA));

	auto matchResTrue = node.match(recordFullMatch, deacFullMatch);
	auto matchResFalse = node.match(recordNoMatch, deacNoMatch);

	ASSERT_TRUE(std::get < 0 > (matchResTrue));
	ASSERT_EQ(std::get < 1 > (matchResTrue), 0);
	ASSERT_EQ(std::get < 2 > (matchResTrue), -2);

	ASSERT_FALSE(std::get < 0 > (matchResFalse));

}

TEST(SpecialMoveDetectionAspect, PatternMatch) {
	special_move::InputPattern inPattern(1.0f,
			{ new special_move::SingleNode(special_move::InputItem(itemNS::DirectionEnum::Down)),
					new special_move::SingleNode(special_move::InputItem(itemNS::DirectionEnum::Up)),
					new special_move::ConjuctionNode(special_move::InputItem(itemNS::KeyPressEnum::KeyA),
							special_move::InputItem(itemNS::KeyPressEnum::KeyB)) });

	special_move::InputRecordType recordFullMatch;

	recordFullMatch.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordFullMatch.push(special_move::InputItem(itemNS::DirectionEnum::Up));
	recordFullMatch.push(special_move::InputItem(itemNS::KeyPressEnum::KeyA));
	recordFullMatch.push(special_move::InputItem(itemNS::KeyPressEnum::KeyB));

	special_move::InputRecordType recordWrongOrder;

	recordWrongOrder.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordWrongOrder.push(special_move::InputItem(itemNS::KeyPressEnum::KeyB));
	recordWrongOrder.push(special_move::InputItem(itemNS::DirectionEnum::Up));
	recordWrongOrder.push(special_move::InputItem(itemNS::KeyPressEnum::KeyA));

	special_move::InputRecordType recordTooSlow;

	recordTooSlow.push(special_move::InputItem(itemNS::DirectionEnum::Down, 0.2f));
	recordTooSlow.push(special_move::InputItem(itemNS::DirectionEnum::Up, 0.1f));
	recordTooSlow.push(special_move::InputItem(itemNS::KeyPressEnum::KeyA, 0.5f));
	recordTooSlow.push(special_move::InputItem(itemNS::KeyPressEnum::KeyB, 0.4f));

	special_move::InputRecordType recordFullMatchNoisy;

	recordFullMatchNoisy.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordFullMatchNoisy.push(special_move::InputItem(itemNS::DirectionEnum::Down));
	recordFullMatchNoisy.push(special_move::InputItem(itemNS::KeyPressEnum::KeyB));
	recordFullMatchNoisy.push(special_move::InputItem(itemNS::KeyPressEnum::Undefined));
	recordFullMatchNoisy.push(special_move::InputItem(itemNS::DirectionEnum::Up));
	recordFullMatchNoisy.push(special_move::InputItem(itemNS::KeyPressEnum::KeyA));
	recordFullMatchNoisy.push(special_move::InputItem(itemNS::KeyPressEnum::KeyB));

	special_move::InputRecordType recordEmptyRecord;
	ASSERT_FALSE(inPattern.match(recordEmptyRecord));

	ASSERT_FALSE(inPattern.match(recordWrongOrder));

	special_move::InputRecordType recordOneEntry;
	recordOneEntry.push(special_move::InputItem(itemNS::KeyPressEnum::KeyB));
	ASSERT_FALSE(inPattern.match(recordOneEntry));

	ASSERT_TRUE(inPattern.match(recordFullMatch));
	// input disabled ?
	for (int i = 0; i >= recordFullMatch.smallestIndex(); i--) {
		ASSERT_TRUE(recordFullMatch.get(i).Used);
	}
	// running this pattern check again should fail, the inputs are marked used
	ASSERT_FALSE(inPattern.match(recordFullMatch));

	ASSERT_FALSE(inPattern.match(recordTooSlow));
	ASSERT_TRUE(inPattern.match(recordFullMatchNoisy));

}

