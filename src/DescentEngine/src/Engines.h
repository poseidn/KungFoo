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
