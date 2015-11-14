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
