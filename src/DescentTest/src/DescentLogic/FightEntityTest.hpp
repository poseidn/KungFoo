#pragma once

#include <gtest/gtest.h>

#include <DescentLogic/src/Entities/FighterEntity.h>

TEST(FighterEntityTest, sekktor) {

	FighterEntity fe(Vector2::Unit(), Rectangle2::Unit());

	fe.setDirection(Vector2(0.0, 0.2).normalizedCopy());
	ASSERT_EQ(fe.getCurrentSekktor(), 0);

	fe.setDirection(Vector2(0.0, -0.2).normalizedCopy());
	ASSERT_EQ(fe.getCurrentSekktor(), 4);

	fe.setDirection(Vector2(-0.2, -0.2).normalizedCopy());
	ASSERT_EQ(fe.getCurrentSekktor(), 5);

	fe.setDirection(Vector2(-0.1, 0.01).normalizedCopy());
	ASSERT_EQ(fe.getCurrentSekktor(), 6);

	fe.setDirection(Vector2(-0.1, 0.1).normalizedCopy());
	ASSERT_EQ(fe.getCurrentSekktor(), 7);

	fe.setDirection(Vector2(-0.001, 0.1).normalizedCopy());
	ASSERT_EQ(fe.getCurrentSekktor(), 0);

}

