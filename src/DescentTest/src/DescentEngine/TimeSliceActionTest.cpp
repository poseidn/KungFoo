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

#include <DescentEngine/src/EntityEngine/TimeSliceAction.h>

TEST(TimeSlice, activate) {
	TimeSliceAction tsa;

	ASSERT_TRUE(tsa.canActivate());
	tsa.activate(1.0f);
	ASSERT_FALSE(tsa.canActivate());
	tsa.validate(0.5f, 0.0f);
	ASSERT_FALSE(tsa.wasJustDisabled());
	ASSERT_FALSE(tsa.canActivate());
	ASSERT_TRUE(tsa.isActive());
	tsa.validate(0.6f, 0.0f);
	ASSERT_TRUE(tsa.wasJustDisabled());
	ASSERT_FALSE(tsa.wasJustDisabled());
	ASSERT_TRUE(tsa.canActivate());
	ASSERT_FALSE(tsa.isActive());
}

