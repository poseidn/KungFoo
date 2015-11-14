#pragma once

#include <boost/noncopyable.hpp>

#include "InputContainer.h"

class NullInput: private boost::noncopyable {
public:
	void updateContainer(InputSystemBase::ContainerArray &, float) {
	}

};
