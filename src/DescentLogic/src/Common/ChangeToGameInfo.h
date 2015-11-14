#pragma once

#include <DescentEngine/src/StateEngine/StateChangeInfo.h>

class ChangeToGameInfo: public StateChangeInfo {
public:
	ChangeToGameInfo(size_t pCount) :
			PlayerCount(pCount) {
	}

	virtual ~ChangeToGameInfo() {
	}

	size_t PlayerCount;
};
