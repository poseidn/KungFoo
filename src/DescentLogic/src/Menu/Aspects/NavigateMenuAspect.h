#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentEngine/src/Input/InputSystem.h>

#include <DescentLogic/src/Menu/MenuState.h>
#include <DescentLogic/src/Entities/GameTemplates.h>

class NavigateMenuAspect: public Aspect<MenuState> {
public:
	NavigateMenuAspect() {
	}

	virtual void init(MenuState & gs) CPP11_OVERRIDE;

private:
	void onSelect(MenuState &, InputSystem::ContainerId);

	void onMove(MenuState &, MenuState::MovementDirection, InputSystem::ContainerId);
	void onEnableDisableDevice(MenuState &, InputSystem::ContainerId);

	void autoSelectDevice(MenuState &, InputSystem::ContainerId);

	PreloadState m_lastPreload;
	bool m_preloading = false;
};
