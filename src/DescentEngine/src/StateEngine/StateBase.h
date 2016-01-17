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

#include <memory>
#include <boost/noncopyable.hpp>

#include "StateChangeInfo.h"

class StateBase: boost::noncopyable {
public:
	StateBase() :
			m_reqStateName(""), m_reqApplicationQuit(false) {

	}

	virtual void onActivateState(StateChangeInfoPtr const& changeInfo) {

	}

	virtual void onDeactivateState() {

	}

	void requestApplicationQuit() {
		m_reqApplicationQuit = true;
	}

	void requestStateChange(std::string const& newStateName, StateChangeInfoPtr changeInfo = nullptr) {
		m_reqStateName = newStateName;
		m_reqStateInfo = changeInfo;
	}

	std::string const& getStateChangeRequest() const {
		return m_reqStateName;
	}

	StateChangeInfoPtr const& getStateChangeRequestInfo() const {
		return m_reqStateInfo;
	}

	bool getApplicationQuitRequest() const {
		return m_reqApplicationQuit;
	}

	void clearStateChangeRequest() {
		m_reqStateName = "";
		m_reqStateInfo = std::make_shared<StateChangeInfo>();
	}

	virtual std::string getDebugState() const {
		return "";
	}

private:
	std::string m_reqStateName;
	bool m_reqApplicationQuit;
	StateChangeInfoPtr m_reqStateInfo;
};
