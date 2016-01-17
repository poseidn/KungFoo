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

#include <iostream>

#include "gtest/gtest.h"

// engine
#include "DescentEngine/SignalsTest.hpp"
#include "DescentEngine/StateEngineTest.hpp"
#include "DescentEngine/StateTransitionTest.hpp"
#include "DescentEngine/EntityEngineTest.hpp"
#include "DescentEngine/RectangleTest.hpp"
#include "DescentEngine/VectorTest.hpp"
#include "DescentEngine/RingBufferTest.hpp"
#include "DescentEngine/SpecialMoveDetectionAspectTest.hpp"
#include "DescentEngine/PathfindingTest.h"

// logic
#include "DescentLogic/LevelLoaderTest.hpp"
#include "DescentLogic/FightEntityTest.hpp"

GTEST_API_ int main(int argc, char **argv) {
	std::cout << "Running main() from gtest_main.cc\n";

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
