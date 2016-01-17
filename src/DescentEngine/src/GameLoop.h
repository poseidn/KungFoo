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

//#include <pthread.h>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>

#include <boost/noncopyable.hpp>

#include "Cpp11.h"

#include "Threading/PortableMutex.h"
#include "Threading/PortableThread.h"

// register for events with a template system ?

#include "Engines.h"

class StateTransitions;

// todo: decrease usage of templates here
class GameLoop CPP11_FINAL : boost::noncopyable {
public:
	static CPP11_CONSTEXPR int UseThreading = 0;

	GameLoop(RenderEngine & re, StateTransitions & trans, EntityEngine& ee, AnimationEngine & an,
			InputSystem & input, PhysicsEngine & phys, bool showFps, bool profile, std::string & profileFileName) :
	m_renderEngine(re), //
	m_stateTransitions(trans),//
	m_entityEngine(ee),//
	m_animationEngine(an),//
	m_inputSystem(input),//
	m_physics(phys),//
	m_showFps(showFps),//
	m_profile(profile),//
	m_profileFileName(profileFileName) {
	}

	/// can be used in an application which does not want to return control
	void run();
	// timeDelta seconds
	bool step(float timeDelta);

	void setInitialContentFunc(std::function<void(void)> f);

	void setRenderInitData(RenderEngine::interface_type::InterfaceDataType const& co) {
		m_initData = co;
	}

private:

	// is only run, if not multi-threaded
	void render();
	void initRender();

	RenderEngine & m_renderEngine;
	StateTransitions & m_stateTransitions;
	EntityEngine & m_entityEngine;
	AnimationEngine & m_animationEngine;
	InputSystem & m_inputSystem;
	PhysicsEngine &m_physics;

	std::mutex m_mutxVertexData;
	//bool m_renderInitialized;
	std::function<void(void)> m_initialContentFunc;
	//std::unique_ptr<PortableThread> m_renderThread;

	RenderEngine::interface_type::InterfaceDataType m_initData;

	// in frames / second
	const float m_maxFramerate = 100.0f;
	const float m_minTime = 1.0f / m_maxFramerate;
	const bool m_showFps;
	const bool m_profile = false;
	std::string m_profileFileName;
	const size_t m_profileDumpRate = 100;
	size_t m_loopIteration = 0;
};
