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

// cannot be forward declared: uses templates
#include "RenderEngine.h"

class ResourceEngine;
class RandomEngine;
class EntityEngine;
class AnimationEngine;
class SoundEngine;
class InputSystem;
class PhysicsEngine;
class ScriptEngine;

class Engines {
public:
	Engines(RenderEngine & re, ResourceEngine & resource, AnimationEngine &ae, EntityEngine & ee,
			SoundEngine & snd, RandomEngine & rand, InputSystem & inp, PhysicsEngine & phys, ScriptEngine & sc) :
			m_re(re), m_resource(resource), m_ae(ae), m_ee(ee), m_snd(snd), m_rand(rand), m_inp(inp), m_physics(
					phys), m_script(sc) {

	}

	RenderEngine & renderEngine() const {
		return m_re;
	}

	ResourceEngine & resourceEngine() const {
		return m_resource;
	}

	AnimationEngine & animationEngine() const {
		return m_ae;
	}

	EntityEngine & entityEngine() const {
		return m_ee;
	}

	SoundEngine & soundEngine() const {
		return m_snd;
	}

	RandomEngine & randomEngine() const {
		return m_rand;
	}

	InputSystem & inputEngine() const {
		return m_inp;
	}

	PhysicsEngine & physicsEngine() const {
		return m_physics;
	}

	ScriptEngine & scriptEngine() const {
		return m_script;
	}

private:

	RenderEngine & m_re;
	ResourceEngine & m_resource;
	AnimationEngine & m_ae;
	EntityEngine & m_ee;
	SoundEngine & m_snd;
	RandomEngine & m_rand;
	InputSystem & m_inp;
	PhysicsEngine & m_physics;
	ScriptEngine & m_script;
};
