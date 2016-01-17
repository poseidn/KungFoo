/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

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
