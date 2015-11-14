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

	// todo: also use suspend here to not kill a game state
	// completely, but merely pause it and don't process user
	// input

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
	ASSERT_EQ(st.getActiveEngine(), state1);

	st.addState("s2", state2);
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

