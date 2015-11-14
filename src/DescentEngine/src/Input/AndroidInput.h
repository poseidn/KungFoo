#pragma once

#include <boost/noncopyable.hpp>

#include "../Cpp11.h"
#include "InputSystemBase.h"
#include "InputContainer.h"

class AndroidInput: private boost::noncopyable {
public:

	AndroidInput();
	~AndroidInput();
	void updateContainer(InputSystemBase::ContainerArray &, float dt);

	void injectDirectionStickOne(InputContainer &, Vector2);
	void injectKeyDown(InputContainer &, InputSystemBase::ContainerId, int);
	void registerInputDevice(int);

	size_t maxInputDevices() const {
		// 4 gamepads ...
		return 4;
	}

	DeviceList availableInputDevices() const;
private:
	std::vector<std::pair<InputSystemBase::ContainerId, int>> m_lastKeyPresses;
	std::vector<int> m_registeredDevices;

};
