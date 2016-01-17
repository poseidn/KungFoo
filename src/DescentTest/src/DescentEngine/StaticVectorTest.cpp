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

#include <gtest/gtest.h>

#include <DescentEngine/src/DataTypes/StaticVector.h>

TEST(StaticVectorTest, push_get) {
	StaticVector<int> sVect;

	auto ref1 = sVect.push_back(23);
	auto ref2 = sVect.push_back(24);
	auto ref3 = sVect.push_back(25);

	ASSERT_EQ(23, ref1.get());
	ASSERT_EQ(24, ref2.get());
	ASSERT_EQ(25, ref3.get());

	ASSERT_EQ(size_t(3), sVect.activeSize());

	sVect.remove(ref2);

	ASSERT_EQ(size_t(2), sVect.activeSize());

	auto ref4 = sVect.push_back(45);
	ASSERT_EQ(int(45), ref4.get());
	ASSERT_EQ(size_t(3), sVect.activeSize());

	auto findInsert = [] ( int const& it ) -> bool {return it > 30;};
	auto ref5 = sVect.push(55, findInsert);
	ASSERT_EQ(int(55), ref5.get());

	// we expect it at positon 2
	ASSERT_EQ(int(55), sVect.get(2));
	ASSERT_EQ(int(45), sVect.get(3));

}

