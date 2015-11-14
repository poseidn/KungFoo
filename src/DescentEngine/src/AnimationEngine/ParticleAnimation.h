#pragma once

#include <boost/noncopyable.hpp>
#include "../Cpp11.h"

class ParticleSystemVisual;

class ParticleAnimation CPP11_FINAL {
public:
	ParticleAnimation(ParticleSystemVisual * visual) :
			m_visual(visual), m_inactive(false) {
	}

	// the animation will be removed, if false is returned here
	bool step(const float deltaT);

	bool isInactive() const {
		return m_inactive;
	}

	void reset();

private:
	ParticleSystemVisual * m_visual;
	bool m_inactive;
};
