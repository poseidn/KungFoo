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
