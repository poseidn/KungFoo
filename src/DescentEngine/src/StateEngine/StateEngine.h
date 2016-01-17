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

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "../Cpp11.h"

#include "Aspect.h"
#include "../Signals.h"
#include "StateChangeInfo.h"

class StateEngineBase: boost::noncopyable {
public:
	virtual ~StateEngineBase() {
	}

	virtual void step(float deltaT) = 0;

	virtual void onActivateState(StateChangeInfoPtr const& changeInfo) {
	}

	virtual void onDeactivateState() {
	}

	virtual void requestStateChange(std::string const& newStateName) = 0;
	virtual std::string const& getStateChangeRequest() const = 0;
	virtual StateChangeInfoPtr const& getStateChangeRequestInfo() const = 0;
	virtual void clearStateChangeRequest() = 0;
	virtual bool getApplicationQuitRequest() const = 0;

	virtual std::string getDebugState() const {
		return "";
	}
};

class NullState: boost::noncopyable {
public:
	slots::Slot<NullState &, float> slotStep;

};

template<class TState>
class StateEngine: public StateEngineBase {
public:
	typedef Aspect<TState> aspect_type;

	StateEngine(TState & state) :
			m_state(state) {

	}

	~StateEngine() {
	}

	void registerAspect(aspect_type * asp) {
		asp->init(m_state);
		m_aspects.push_back(asp);
	}

	virtual void step(float deltaT) CPP11_OVERRIDE
	{
		m_state.slotStep.signal(m_state, deltaT);
	}

	virtual void onActivateState(StateChangeInfoPtr const& changeInfo) CPP11_OVERRIDE {
		m_state.onActivateState(changeInfo);
	}

	virtual void onDeactivateState() CPP11_OVERRIDE {
		m_state.onDeactivateState();
	}
	void requestStateChange(std::string const& newStateName) CPP11_OVERRIDE {
		m_state.requestStateChange(newStateName);
	}

	std::string const& getStateChangeRequest() const CPP11_OVERRIDE {
		return m_state.getStateChangeRequest();
	}

	StateChangeInfoPtr const& getStateChangeRequestInfo() const CPP11_OVERRIDE {
		return m_state.getStateChangeRequestInfo();
	}

	bool getApplicationQuitRequest() const CPP11_OVERRIDE {
		return m_state.getApplicationQuitRequest();
	}

	void clearStateChangeRequest() CPP11_OVERRIDE {
		m_state.clearStateChangeRequest();
	}

	TState & getState() {
		return m_state;
	}

	TState const& getState() const {
		return m_state;
	}

	virtual std::string getDebugState() const CPP11_OVERRIDE {
		return m_state.getDebugState();
	}

private:
	TState & m_state;
	boost::ptr_vector<aspect_type> m_aspects;
};
