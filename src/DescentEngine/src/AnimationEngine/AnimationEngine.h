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

#include "../Util.h"
#include "../Cpp11.h"
#include "../Visuals/SpriteVisualList.h"
#include "TextAnimation.h"
#include "EntityAnimation.h"
#include "ParticleAnimation.h"

#include <boost/noncopyable.hpp>
#include <list>

// todo: animation system could also use a integer timing system to be faster and save memory...
class AnimationEngine CPP11_FINAL : boost::noncopyable {
public:
	typedef std::list< uniq<EntityAnimationBase>> EntityAnimationList;
	typedef std::list<ParticleAnimation> ParticleAnimationList;
	typedef std::list<TextAnimation> TextAnimationList;

	void step(const float deltaT);

	void addEntityAnimation(uniq<EntityAnimationBase> anim);

	void addParticleAnimation(ParticleAnimation const& an);

	void addTextAnimation(TextAnimation const& an);

	void clearAll();

private:

	EntityAnimationList m_entityAnimations;
	ParticleAnimationList m_particleAnimations;
	TextAnimationList m_textAnimations;
};
