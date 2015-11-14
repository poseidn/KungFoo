#include "TextAnimation.h"

#include "../Visuals/TextVisual.h"

bool TextAnimation::step(const float deltaT) {

	assert(m_visual);

	if (m_offsetBeforeFadeout < 0.0f) {
		m_nextStep -= deltaT;
		const float transparency = std::max(0.0f, m_nextStep / m_stepTime);

		m_visual->setTransparency(transparency);

		if (m_nextStep < 0.0f) {
			// we are sooo DONE !
			// mark to remove
			if (m_removeTextOnAnimationComplete) {
				m_visual->setToRemove();
				// cannot use this any more, as the render engine might remove it at any time
				m_visual = nullptr;
			}

			// signals this animation can be removed
			return false;
		}

	} else {
		m_offsetBeforeFadeout -= deltaT;
	}

	// signal this animation will need to be kept running
	return true;
}

