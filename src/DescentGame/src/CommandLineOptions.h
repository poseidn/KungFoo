#pragma once

#include <boost/program_options.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace po = boost::program_options;

namespace commandline {

bool handleCommandLine(SDLInterfaceInitData & sdlInitData, std::vector<std::string> & options,
		bool & runDemoMode, bool & muted, bool & forwardScroll, bool & withIntro) {

	const std::string tagHelp = "help";
	const std::string tagResolution = "resolution";
	const std::string tagNoFullscreen = "noFullscreen";
	const std::string tagDemo = "demo";
	const std::string tagMute = "mute";
	const std::string tagNoScroll = "noScroll";
	const std::string tagNoIntro = "noIntro";

	po::options_description desc("Allowed options");
	desc.add_options()(tagHelp.c_str(), "shows this very useful help screen");
	desc.add_options()(tagResolution.c_str(), po::value<std::string>(), "set resolution (like 1024x768)");
	desc.add_options()(tagNoFullscreen.c_str(), "run in windowed mode");
	desc.add_options()(tagDemo.c_str(), "run in demo mode");
	desc.add_options()(tagMute.c_str(), "mute all sound output");
	desc.add_options()(tagNoScroll.c_str(), "don't forward scroll in the game mode");
	desc.add_options()(tagNoIntro.c_str(), "don't show the intro");

	po::variables_map vm;

	po::store(po::command_line_parser(options).options(desc).run(), vm);
	po::notify(vm);

	if (vm.count(tagHelp)) {
		std::cout << desc << std::endl;
		return false;
	}

	sdlInitData.Fullscreen = (vm.count(tagNoFullscreen) == 0);
	runDemoMode = (vm.count(tagDemo) > 0);
	muted = (vm.count(tagMute) > 0);
	forwardScroll = (vm.count(tagNoScroll) == 0);
	withIntro = (vm.count(tagNoIntro) == 0);

	if (vm.count(tagResolution)) {
		const std::string resoString(vm[tagResolution].as<std::string>());
		std::cout << "resolution is set to " << std::endl;

		// parse resolution
		std::vector < std::string > strs;
		boost::split(strs, resoString, boost::is_any_of("x"));

		if (strs.size() != 2) {
			logging::Fatal() << "Cannt parse resolution string";
			return false;
		}

		sdlInitData.Resolution = Vector2Uint(boost::lexical_cast<int>(strs[0]),
				boost::lexical_cast<int>(strs[1]));

		sdlInitData.ResolutionSet = true;
	}

	// continue with execution
	return true;
}

}
