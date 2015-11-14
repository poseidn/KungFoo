#pragma once

#include <DescentEngine/src/StateEngine/StateChangeInfo.h>

class GameToMenuInfo: public StateChangeInfo {
public:

	GameToMenuInfo() :
			PlayerDied(false), FinalScore(0), PlayerCount(0) {
	}

	virtual ~GameToMenuInfo() {
	}

	bool PlayerDied;
	int FinalScore;
	int PlayerCount;
};
