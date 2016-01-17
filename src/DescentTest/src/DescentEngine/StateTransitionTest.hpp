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

#include <gtest/gtest.h>

#include <DescentEngine/src/Cpp11.h>

#include <DescentEngine/src/StateEngine/StateEngine.h>
#include <DescentEngine/src/StateEngine/StateBase.h>
#include <DescentEngine/src/StateEngine/StateTransitions.h>

class TestState: public StateEngineBase {
public:
	TestState() :
			m_act(0), m_deact(0) {
	}

	void step(float deltaT) CPP11_OVERRIDE {

	}

	void onActivateState(StateChangeInfoPtr const& changeInfo) CPP11_OVERRIDE {
		m_act++;
	}

	void onDeactivateState() CPP11_OVERRIDE {
		m_deact++;
	}

	void requestStateChange(std::string const& newStateName) CPP11_OVERRIDE {
		m_reqChange = newStateName;
	}

	std::string const& getStateChangeRequest() const CPP11_OVERRIDE {
		return m_reqChange;
	}

	StateChangeInfoPtr const& getStateChangeRequestInfo() const CPP11_OVERRIDE {
		return m_changeInfo;
	}

	bool getApplicationQuitRequest() const CPP11_OVERRIDE {
		return false;
	}

	void clearStateChangeRequest() CPP11_OVERRIDE {
		m_reqChange = "";
	}

	int m_act;
	int m_deact;
	std::string m_reqChange;
	StateChangeInfoPtr m_changeInfo;
};

TEST(StateTransitions, switchStates) {
	StateTransitions st;

	TestState * state1 = new TestState();
	TestState * state2 = new TestState();

	ASSERT_EQ(st.getActiveEngine(), nullptr);

	st.addState("s1", state1);
	st.addState("s2", state2);

	// state is only loaded after the first step() call
	st.step(0.1f);
	ASSERT_EQ(st.getActiveEngine(), state1);

	st.setActiveEngine("s2");

	ASSERT_EQ(st.getActiveEngine(), state2);
	ASSERT_EQ(state1->m_deact, 1);
	ASSERT_EQ(state1->m_act, 1);
	ASSERT_EQ(state2->m_deact, 0);
	ASSERT_EQ(state2->m_act, 1);

	st.setActiveEngine("s1");
	ASSERT_EQ(state1->m_deact, 1);
	ASSERT_EQ(state1->m_act, 2);
	ASSERT_EQ(state2->m_deact, 1);
	ASSERT_EQ(state2->m_act, 1);
}

