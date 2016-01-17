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

#include <cstddef>
#include "RenderEngineBenckmark.h"

#include <DescentEngine/src/Visuals/SpriteVisual.h>
#include <DescentEngine/src/Log.h>

/*
 * run with
 * perf stat EngineBench/RenderEngineBench
 * perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations EngineBench/RenderEngineBenchu
 */

int main(int argc, const char* argv[]) {

	RenderEngineBenchmark re;

	const size_t numSprites = 5000;

	logging::Info() << "Starting Render Engine benchmark with " << numSprites << " numSprites";

	for (size_t i = 0; i < numSprites; i++) {
		re.addSpriteVisual(
				SpriteVisual(ScreenTransform(), nullptr, Vector2(1, 2), Vector2(1, 1), LayerPriorityBottom));
	}

	for (long i = 0; i < 5000000000; i++) {
		re.render(0.1f);
	}

	return 0;
}
