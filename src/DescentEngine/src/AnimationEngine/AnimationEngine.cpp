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

#include "AnimationEngine.h"

#include <vector>
#include <functional>

#include "EntityAnimation.h"
#include "ParticleAnimation.h"
#include "TextAnimation.h"

void AnimationEngine::clearAll() {
	m_particleAnimations.clear();
	m_textAnimations.clear();
	m_entityAnimations.clear();
}

void AnimationEngine::step(const float deltaT) {

	// android's ndk needs the lambdas explicit ...

	std::function<bool(TextAnimation&)> textRemove =
			[deltaT]( TextAnimation & p ) ->bool {return !p.step(deltaT);};
	util::erase_if(m_textAnimations, textRemove);

	std::function<bool(ParticleAnimation&)> animRemove =
			[deltaT]( ParticleAnimation & p ) ->bool {return !p.step(deltaT);};
	util::erase_if(m_particleAnimations, animRemove);

	std::function<bool(uniq<EntityAnimationBase> &)> entRemove = [deltaT]( uniq<EntityAnimationBase> & p ) {
		if (p->decreaseDuration(deltaT)) {
			// animation still running
			p->step(deltaT);
			return false;
		} else {
			// animation is done and needs to be killed
			return true;
		}
	};
	util::erase_if(m_entityAnimations, entRemove);

}

void AnimationEngine::addEntityAnimation(uniq<EntityAnimationBase> anim) {
	m_entityAnimations.push_back(std::move(anim));
}

void AnimationEngine::addParticleAnimation(ParticleAnimation const& an) {
	m_particleAnimations.push_back(an);
}

void AnimationEngine::addTextAnimation(TextAnimation const& an) {
	m_textAnimations.push_back(an);
}

