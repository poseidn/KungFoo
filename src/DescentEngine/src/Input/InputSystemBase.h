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

#include <map>
#include <vector>
#include <boost/noncopyable.hpp>

#include "../Log.h"
#include "../Cpp11.h"
#include "../Util.h"
#include "InputContainer.h"

class InputDevice {
public:
	enum class TypeEnum {
		Keyboard, Gamepad, Touchpad
	};

	InputDevice(TypeEnum type, int index, std::string name) :
			Type(type), Index(index), Name(name) {

	}

	TypeEnum Type;
	// -1 as index will be keyboard
	int Index;
	std::string Name;
};

typedef std::vector<InputDevice> DeviceList;

class InputSystemBase: boost::noncopyable {

public:

	CPP11_CONSTEXPR static size_t MaxPlayerInput = 2;

	typedef int PlayerInputId;
	typedef int ContainerId;CPP11_CONSTEXPR static ContainerId InvalidContainerId =
			-1000;

	InputSystemBase() {

	}

	//typedef std::pair<PlayerInputEnum, InputContainer> PlayerInputContainer;

	// each input device get's its input container
	// just if we will look there is another question ....
	typedef std::map<ContainerId, InputContainer> ContainerArray;
	typedef std::map<PlayerInputId, ContainerId> PlayerAssignment;

	// per-frame call which allows the concrete input system
	// to query the current state of its input devices and update
	// the input containers accordingly
	virtual void updateContainer(float deltaT) = 0;

	InputContainer const& getContainerConst(PlayerInputId pl) {
		// find assignment
		return getContainer(pl);
	}

	void resetPlayerAssignment() {
		logging::Info() << "Reseting player assignment";
		m_playerAssignment.clear();
	}

	void assignPlayerToInput(PlayerInputId pl, ContainerId containerId) {
		m_playerAssignment[pl] = containerId;
		logging::Info() << "Assiging player " << pl << " to containerId"
				<< containerId;
	}

	void dumpPlayerAssignment() const {
		logging::Info() << "dumping player assignment";
		for (auto pAss : m_playerAssignment) {
			logging::Info() << "PlayerInputId" << pAss.first << " mapped to "
					<< pAss.second;
		}
	}

	virtual void showVirtualControls() {
	}
	virtual void hideVirtualControls() {
	}

	// convinience functions which condenses multiple input containers

	typedef std::pair<bool, ContainerId> AnyResultKey;
	typedef std::pair<Vector2, ContainerId> AnyResultDirection;

	AnyResultKey any_keyDownExit() const {
		for (auto const& c : m_cont) {
			if (c.second.keyDownExit())
				return std::make_pair(true, c.first);
		}
		return std::make_pair(false, 0);
	}

	AnyResultKey any_keyDownKick() const {
		for (auto const& c : m_cont) {
			if (c.second.keyDownKick())
				return std::make_pair(true, c.first);
		}
		return std::make_pair(false, 0);
	}

	AnyResultKey any_keyDownJump() const {
		for (auto const& c : m_cont) {
			if (c.second.keyDownJump())
				return std::make_pair(true, c.first);
		}
		return std::make_pair(false, 0);
	}

	AnyResultKey any_isStickOneMoved() const {
		for (auto const& c : m_cont) {
			if (c.second.isStickOneMoved())
				return std::make_pair(true, c.first);
		}
		return std::make_pair(false, 0);
	}

	AnyResultDirection any_directionStickOne() const {
		Vector2 dir;
		ContainerId contId(InvalidContainerId);
		for (auto const& c : m_cont) {
			// find the stick which moved ... thats all we can do
			if (c.second.isStickOneMoved())
				contId = c.first;

			dir = dir + c.second.directionStickOne();
		}
		return std::make_pair(dir, contId);
	}

protected:

// only called by various input classes to get r/w access to the
// container with updateContainer() being calledS
	InputContainer & getContainer(PlayerInputId pl) {
		ContainerId id = getPlayerAssignment(pl);

		util::initMap(m_cont, id);

		return m_cont[id];
	}

	InputContainer & getContainerByContainerId(ContainerId id) {
		util::initMap(m_cont, id);

		return m_cont[id];
	}

	ContainerArray & getContainers() {
		return m_cont;
	}

	ContainerId getPlayerAssignment(PlayerInputId pl) const {
		auto const& assignment = m_playerAssignment.find(pl);
		if (assignment == m_playerAssignment.end()) {
			logging::Fatal()
					<< "reqesting input container for non-assigned player";
		}
		return assignment->second;
	}
	/*
	 size_t getPlayerLocation(PlayerInputEnum pl) const {
	 if (pl == PlayerInputEnum::PlayerOne)
	 return 0;
	 else if (pl == PlayerInputEnum::PlayerTwo)
	 return 1;
	 else
	 logging::Fatal() << "Player number not supported";

	 return 0;
	 }*/

private:
	ContainerArray m_cont;
	PlayerAssignment m_playerAssignment;

};
