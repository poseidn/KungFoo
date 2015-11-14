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
