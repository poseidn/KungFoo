#include "ParticleAnimation.h"

#include "../Visuals/ParticleSystemVisual.h"

bool ParticleAnimation::step(const float deltaT) {

	if (m_visual->m_runtime > 0.0f) {
		// move
		for (size_t i = 0; i < m_visual->m_verticesLocation.size(); i++) {

			const float dX = m_visual->m_verticesVelo[i].x() * deltaT;
			const float dY = m_visual->m_verticesVelo[i].y() * deltaT;

			m_visual->m_verticesLocation[i] = m_visual->m_verticesLocation[i] + Vector2(dX, dY);
		}

		m_visual->update(m_visual->m_trans);
		m_visual->m_runtime -= deltaT;

		// fade out with alpha at the end of the animation
		if (m_visual->m_runtime < 0.33f) {
			const float alpha = m_visual->m_runtime * 3.0f;
			m_visual->m_color[3] = alpha;
		}
	} else {
		if (m_visual->getVisible()) {
			m_visual->setVisible(false);
			m_visual->setToRemove();
			m_inactive = true;
			return false;
		}
	}

	return true;
}

void ParticleAnimation::reset() {

}
