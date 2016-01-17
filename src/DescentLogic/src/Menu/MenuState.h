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

#include <list>

#include <boost/noncopyable.hpp>

#include <DescentEngine/src/Input/InputSystem.h>
#include <DescentEngine/src/Signals.h>
#include <DescentEngine/src/Engines.h>

#include <DescentEngine/src/StateEngine/StateBase.h>

#include <DescentEngine/src/EntityEngine/Entity.h>
#include <DescentEngine/src/EntityEngine/EntityList.h>

class InputContainer;

class MenuItem {
public:
	MenuItem(std::string id, std::string text, Vector2 markerPos) :
			Id(id), Text(text), MarkerPos(markerPos), TextVis(nullptr) {

	}

	std::string Id;
	std::string Text;
	Vector2 MarkerPos;
	TextVisual * TextVis;
	bool Selectable;
};

class MenuState: public StateBase {
public:
	enum class MovementDirection {
		Up, Down
	};

	MenuState(Engines & eg) :
			StateBase(), m_engines(eg), m_currentItemPointer(nullptr) {

	}

	virtual ~MenuState() {
	}

	slots::Slot<MenuState &, float> slotStep;

	slots::Slot<MenuState &, StateChangeInfoPtr const&> slotActivateState;
	slots::Slot<MenuState &> slotDeactivateState;

	slots::Slot<MenuState &, InputSystem::ContainerId> slotInputSelect;
	slots::Slot<MenuState &, InputSystem::ContainerId> slotInputEnable;
	slots::Slot<MenuState &, MovementDirection, InputSystem::ContainerId> slotInputMove;
	slots::Slot<MenuState &, bool> slotDebugSwitchRenderTiles;

	virtual void onActivateState(StateChangeInfoPtr const& changeInfo) CPP11_OVERRIDE {
		slotActivateState.signal(*this, changeInfo);
	}

	virtual void onDeactivateState() CPP11_OVERRIDE {
		slotDeactivateState.signal(*this);
	}

	Engines & getEngines() {
		return m_engines;
	}

	ManagedEntityList & getManagedEntityList() {
		return m_managedEntities;
	}

	std::vector<MenuItem> & getMenuItemList() {
		return m_menuItems;
	}

	void addMenuItem(MenuItem & item);

	void bootstrapMenu();

	void moveMenuPointer(MovementDirection dir);

	void setCurrentItem(int item);

	void setDeviceItemVisible(bool);

	size_t activeDevices() const;
	void updateDevices();

	void setMenuVisible(bool v);

	std::string getCurrentItemId() const;

	// todo: clean this stuff up
	struct DeviceItem {
		//Dev
		bool m_isEnabled;

		InputSystem::ContainerId m_ContainerId;
		InputDevice::TypeEnum m_type;

		Entity * m_Icon = nullptr;
		Entity * m_IconPassive = nullptr;
		Entity * m_EnableText = nullptr;
		Entity * m_DisableText = nullptr;
	};

	typedef std::vector<DeviceItem> DeviceItems;

	void addDeviceItem(DeviceItem & di) {
		m_deviceItems.push_back(di);
	}

	DeviceItems & getDeviceItems() {
		return m_deviceItems;
	}

	DeviceItems const& getDeviceItems() const {
		return m_deviceItems;
	}

	Entity * getLoadingPane() {
		return m_loadingPane;
	}

	Entity * getCurrentItemPointer() {
		return m_currentItemPointer;
	}

private:
	Engines & m_engines;

	ManagedEntityList m_managedEntities;
	std::vector<MenuItem> m_menuItems;
	Entity * m_currentItemPointer;
	Entity * m_loadingPane;
	int m_currentItem;
	bool m_deviceItemVisible = true;
	DeviceItems m_deviceItems;

};
