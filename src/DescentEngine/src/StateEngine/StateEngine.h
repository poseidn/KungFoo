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
