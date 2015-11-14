#pragma once

#include <gtest/gtest.h>

#include <DescentEngine/src/DataTypes/RingBuffer.h>

TEST(RingBufferTest, addAndRead) {
	RingBuffer<int, 4> buffer;

	EXPECT_EQ(buffer.size(), size_t(0));

	buffer.push(1);
	buffer.push(2);
	EXPECT_EQ(buffer.size(), size_t(2));

	buffer.push(3);
	buffer.push(4);

	// get most recent item
	EXPECT_EQ(buffer.size(), size_t(4));
	EXPECT_EQ(buffer.get(0), 4);
	EXPECT_EQ(buffer.get(-1), 3);
	EXPECT_EQ(buffer.get(-2), 2);
	EXPECT_EQ(buffer.get(-3), 1);
	// automatic wrap-around
	EXPECT_EQ(buffer.get(-4), 4);
	EXPECT_EQ(buffer.get(-5), 3);
	// in both directions
	EXPECT_EQ(buffer.get(1), 1);
	EXPECT_EQ(buffer.get(2), 2);

	// overwrite
	buffer.push(23);
	EXPECT_EQ(buffer.get(0), 23);
	EXPECT_EQ(buffer.get(-1), 4);
	EXPECT_EQ(buffer.get(-2), 3);
	EXPECT_EQ(buffer.get(-3), 2);

	for (int i = 0; i < 20; i++) {
		buffer.push(42);
	}

	// can never be bigger than 4. It's a ring buffer baby
	EXPECT_EQ(buffer.size(), size_t(4));
}

