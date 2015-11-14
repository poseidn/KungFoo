#include "SDLInput.h"

#include "../Log.h"

// todo: move this into a initialize function
SDLInput::SDLInput() {

	SDL_Init(SDL_INIT_JOYSTICK);

	// open all available gamepads as any one could be used to join the game

	DeviceList dl = availableInputDevices();
	for (InputDevice const& ip : dl) {
		if (ip.Type == InputDevice::TypeEnum::Gamepad) {
			logging::Info() << "Opening gamepad with name " << ip.Name << " and device index " << ip.Index;

			SDL_Joystick * handle = SDL_JoystickOpen(ip.Index);
			if (handle == nullptr) {
				logging::Info() << "could not open gamepad";
			} else {
				logging::Info() << "gamepad opened";
				m_gamepadHandles[ip.Index] = handle;
			}
		}
	}
	SDL_JoystickEventState(SDL_ENABLE);

}

DeviceList SDLInput::availableInputDevices() const {
	DeviceList devList;

	// we always have a keyboard on this platform
	devList.push_back(InputDevice(InputDevice::TypeEnum::Keyboard, -1, "Keyboard"));

	// Note: Xbox 360 wireles controller will report 4 gamepads here
	// but actual events only come from the first gamepad ( index 0 )
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		const std::string jName(SDL_JoystickName(i));
		devList.push_back(InputDevice(InputDevice::TypeEnum::Gamepad, i, jName));
	}

	return devList;
}

SDLInput::~SDLInput() {
	// close joystick, if it was open
	for (auto & pad : m_gamepadHandles) {
		SDL_JoystickClose(pad.second);
	}
}
/*
 bool SDLInput::isGamepadAvailable() {
 return m_joystickHandle != nullptr;
 }*/

void SDLInput::updateContainer(InputSystemBase::ContainerArray & containers, float) {

	while (SDL_PollEvent(&m_event)) {
		switch (m_event.type) {
		case SDL_KEYDOWN:
			if (m_event.key.keysym.sym == SDLK_ESCAPE) {
				containers[-1].setKeyDownExit(true);
			}

			if (m_event.key.keysym.sym == SDLK_RETURN) {
				containers[-1].setKeyDownKick(true);
			}

			if (m_event.key.keysym.sym == SDLK_SPACE) {
				containers[-1].setKeyPressDebug1(true);
			}

			if (m_event.key.keysym.sym == SDLK_v) {
				containers[-1].setKeyPressDebug2(true);
			}

			// to here to disallow auto-fire like usage
			if (m_event.key.keysym.sym == SDLK_LCTRL) {
				containers[-1].setKeyDownKick(true);
			}

			if (m_event.key.keysym.sym == SDLK_m) {
				containers[-1].setKeyDownMenu(true);
			}

			break;
		case SDL_JOYBUTTONDOWN:
			if (m_event.jbutton.type == SDL_JOYBUTTONDOWN) {

				const int gamepadNum = m_event.jbutton.which;

				logging::Info() << "Gamepad num " << gamepadNum << "has event";

				//logging::Info() << "JButton " << float(m_event.jbutton.button);
				if (m_event.jbutton.button == GamepadXBoxStart) {
					containers[gamepadNum].setKeyPressDebug1(true);
				}

				if (m_event.jbutton.button == GamepadXBoxA) {
					containers[gamepadNum].setKeyDownKick(true);
				}

				if (m_event.jbutton.button == GamepadXBoxB) {
					containers[gamepadNum].setKeyDownJump(true);
				}

				if (m_event.jbutton.button == GamepadXBoxC) {
					containers[gamepadNum].setKeyDownBiking(true);
				}

				if (m_event.jbutton.button == GamepadXBoxD) {
					containers[gamepadNum].setKeyDownMenu(true);
				}
			}
			break;
		}
	}

	{
		// only for keyboard
		Vector2 movement(0.f, 0.0f);

		Uint8 * keystate = SDL_GetKeyState(NULL);
		if (keystate[SDLK_UP]) {
			movement = movement + Vector2(0.0f, InputContainer::StickOneMax);
		}
		if (keystate[SDLK_DOWN]) {
			movement = movement + Vector2(0.0f, -InputContainer::StickOneMax);
		}
		if (keystate[SDLK_LEFT]) {
			movement = movement + Vector2(-InputContainer::StickOneMax, 0.0f);
		}
		if (keystate[SDLK_RIGHT]) {
			movement = movement + Vector2(InputContainer::StickOneMax, 0.0f);
		}
		if (keystate[SDLK_LALT]) {
			containers[-1].setKeyDownJump(true);
		}

		if (keystate[SDLK_r]) {
			containers[-1].addInputKey("r");
		}
		if (keystate[SDLK_c]) {
			containers[-1].addInputKey("c");
		}

		containers[-1].setDirectionStickOne(movement);
	}

	//SDL_JoystickUpdate();
	for (auto & pad : m_gamepadHandles) {
		Vector2 movement(0.f, 0.0f);
		SDL_Joystick * gamepadPtr = pad.second;

		const Sint16 xAxis = SDL_JoystickGetAxis(gamepadPtr, 0);
		const Sint16 yAxis = SDL_JoystickGetAxis(gamepadPtr, 1);

		//logging::Info() << "x: " << xAxis << " y: " << yAxis;

		movement = movement + Vector2(InputContainer::StickOneMax * (float(xAxis) / float(GamepadMax)), 0.0f);
		movement = movement + Vector2(0.0f, -InputContainer::StickOneMax * (float(yAxis) / float(GamepadMax)));
		//logging::Info() << "final move x: " << movement.x();

		containers[pad.first].setDirectionStickOne(movement);
	}

}

