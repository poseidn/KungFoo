#pragma once

#include <string>

class EntityEngine;
class ResourceEngine;

struct PreloadState {
	PreloadState() :
			nextLoad(0), allLoads(0) {

	}

	PreloadState(size_t l, size_t al) :
			nextLoad(l), allLoads(al) {
	}

	bool loadDone() const {
		// because nextLoad is zero indexed
		return nextLoad >= allLoads;
	}

	size_t nextLoad = 0;
	size_t allLoads = 1;

};

class GameTemplates {
public:
	static void registerTemplates(EntityEngine & entNg);
	static PreloadState preload(EntityEngine & entNg, ResourceEngine & re, PreloadState pl);
private:
	GameTemplates() {
	}
};
