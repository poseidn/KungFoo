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

#include <DescentEngine/src/VectorTypes.h>

TEST(VectorTest, intersectLines) {

	Line2d a(Vector2(0.0f, 5.0f), Vector2(1.0f, 0.0f));
	Line2d b(Vector2(5.0f, 0.0f), Vector2(0.0f, 1.0f));

	auto intersect = VectorSupport::intersectLines(a, b);

	ASSERT_TRUE( intersect.first);
	ASSERT_FLOAT_EQ( intersect.second.x(), 5.0f);
	ASSERT_FLOAT_EQ( intersect.second.y(), 5.0f);

	Line2d c(Vector2(0.0f, 10.0f), Vector2(0.0f, -1.0f));
	Line2d d(Vector2(-4.0f, 2.0f), Vector2(1.0f, 0.0f));

	intersect = VectorSupport::intersectLines(c, d);

	ASSERT_TRUE( intersect.first);
	ASSERT_FLOAT_EQ( intersect.second.x(), 0.0f);
	ASSERT_FLOAT_EQ( intersect.second.y(), 2.0f);

	Line2d a_par(Vector2(5.0f, 0.0f), Vector2(0.0f, 1.0f));
	Line2d b_par(Vector2(0.0f, 4.0f), Vector2(0.0f, 1.0f));

	intersect = VectorSupport::intersectLines(a_par, b_par);

	ASSERT_FALSE( intersect.first);
}

TEST(VectorTest, angleBetweenVectors) {

	Vector2 vec_right(2.0f, 0.0f);
	Vector2 vec_top(0.0f, 12.0f);
	Vector2 vec_left(-2.0f, 0.0f);
	Vector2 vec_bottom(0.0f, -312.0f);

	ASSERT_FLOAT_EQ(Vector2::angleBetween( vec_right, vec_right *2.0f ), 0.0f);
	ASSERT_FLOAT_EQ(Vector2::angleBetween( vec_top, vec_right ), M_PI * 0.5f);
	ASSERT_FLOAT_EQ(Vector2::angleBetween( vec_left, vec_top ), M_PI * 0.5f);
	ASSERT_FLOAT_EQ(Vector2::angleBetween( vec_bottom, vec_top ), M_PI);

	ASSERT_FLOAT_EQ(
			Vector2::angleBetween( vec_bottom.normalizedCopy() + vec_right.normalizedCopy(), vec_right.normalizedCopy() + vec_top.normalizedCopy() ),
			M_PI*0.5f);
}

