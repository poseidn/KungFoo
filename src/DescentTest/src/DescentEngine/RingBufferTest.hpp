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

