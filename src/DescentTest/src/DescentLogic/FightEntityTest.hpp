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

