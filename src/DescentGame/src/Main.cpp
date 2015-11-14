#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <DescentLogic/src/DescentFramework.h>

//#include "CommandLineOptions.h"

// set via the build system, if a profile is needed
#ifdef USE_PROFILER
#include <gperftools/profiler.h>
#endif

namespace po = boost::program_options;

// use ./DescentGame --fullscreen --resolution 1366x768
// on the notebook for the total fun

int main(int argc, const char* argv[]) {
	SDLInterfaceInitData sdlInitData;

	std::vector < std::string > opts;

	for (int i = 0; i < argc; i++) {
		opts.push_back(std::string(argv[i]));
	}

	// running fullscreen is default
	sdlInitData.Fullscreen = false;
	bool runDemoMode = false;
	bool muted = false;
	bool forwardScroll = false;
	bool withIntro = false;
/*
	if (commandline::handleCommandLine(sdlInitData, opts, runDemoMode, muted, forwardScroll, withIntro)
			== false)
		return 0;*/

	DescentFramework f(false, runDemoMode, muted, forwardScroll, withIntro, true);

	f.initRenderEngine(sdlInitData);

	// todo: make this a lot nicer, by templating the FW class
#ifdef USE_PROFILER
	ProfilerStart("GameLoop.perf");
#endif

	f.execute();

#ifdef USE_PROFILER
	ProfilerStop();
#endif

	// done globally here for all used SDL systems;
	SDL_Quit();

	return 0;
}
