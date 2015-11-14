#pragma once

#include <gtest/gtest.h>

#include <DescentEngine/src/Rectangle.h>

TEST(RectangleTest, toGlobalCoords) {
	Vector2 globalPos(10.0f, 20.0f);
	Rectangle2 rect(6.0f, 2.0f);

	ASSERT_FLOAT_EQ( 7.0f, rect.getUpperLeftGlobal( globalPos).x());
	ASSERT_FLOAT_EQ( 21.0f, rect.getUpperLeftGlobal( globalPos).y());

	ASSERT_FLOAT_EQ( 13.0f, rect.getLowerRightGlobal( globalPos).x());
	ASSERT_FLOAT_EQ( 19.0f, rect.getLowerRightGlobal( globalPos).y());

}

