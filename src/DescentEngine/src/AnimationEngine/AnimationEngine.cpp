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

