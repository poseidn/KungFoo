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
