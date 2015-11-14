#include <DescentEngine/src/Input/InputContainer.h>
#include "AndroidInput.h"

#include <sstream>
#include "../Log.h"

AndroidInput::AndroidInput() {

}

AndroidInput::~AndroidInput() {

}

void AndroidInput::injectDirectionStickOne(InputContainer & cont, Vector2 newMovement) {
	cont.setDirectionStickOne(newMovement);

}

DeviceList AndroidInput::availableInputDevices() const {
	DeviceList devList;

	for (auto i : m_registeredDevices) {
		std::stringstream sId;
		sId << "AndroidInput" << i;
		devList.push_back(InputDevice(InputDevice::TypeEnum::Gamepad, i, sId.str()));
	}

	// todo: has to be delivered by android
	return devList;
}

void AndroidInput::injectKeyDown(InputContainer & cont, InputSystemBase::ContainerId devId, int keyId) {
	m_lastKeyPresses.push_back(std::make_pair(devId, keyId));
}

void AndroidInput::registerInputDevice(int devId) {
	m_registeredDevices.push_back(devId);
	logging::Info() << "Registered input device with id " << devId << " coming from android";
}

void AndroidInput::updateContainer(InputSystemBase::ContainerArray & cont, float dt) {

	for (auto & c : cont) {
		InputContainer & container = c.second;
		container.resetKeypress();

		for (auto & kp : m_lastKeyPresses) {
			if (c.first == kp.first) {

				const int keyId = kp.second;

				if (keyId == 1) {
					container.setKeyDownKick(true);
				}
				if (keyId == 2) {
					container.setKeyDownJump(true);
				}
				if (keyId == 3) {
					container.setKeyPressDebug1(true);
				}
				if (keyId == 4) {
					container.setKeyDownMenu(true);
				}
			}
		}

	}

	m_lastKeyPresses.clear();
}
