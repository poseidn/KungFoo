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

#include <DescentEngine/src/Util.h>

#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

TEST(UniqListTest, zero_erase) {
	std::list<int> myInt;

	// can only delete if not at the end already, needs to be checked here
	auto toRem = std::remove_if(myInt.begin(), myInt.end(), [](int & iRef) {return true;});
	myInt.erase(toRem, myInt.end());
}

TEST(UniqListTest, util_erase_if) {
	std::list<int> myInt;

	// should not crash
	util::erase_if(myInt, [](int & iRef) {return true;});

	myInt = { {1,2,3,4,5,6}};

	util::erase_if(myInt, [](int & iRef) {return (iRef % 2) == 0;});
	ASSERT_EQ(size_t(3), myInt.size());
}
