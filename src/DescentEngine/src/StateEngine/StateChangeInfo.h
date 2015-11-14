#pragma once

#include <memory>

class StateChangeInfo {
public:
	virtual ~StateChangeInfo() {
	}
};

typedef std::shared_ptr<StateChangeInfo> StateChangeInfoPtr;
