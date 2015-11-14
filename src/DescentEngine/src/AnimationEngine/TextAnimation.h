#pragma once

#include <boost/noncopyable.hpp>
#include "../Cpp11.h"

class TextVisual;

class TextAnimation CPP11_FINAL {
public:
	TextAnimation(TextVisual * visual, float offsetBeforeFadeout, float fadeOutTime,
			bool removeTextOnAnimationComplete) :
	m_visual(visual), m_offsetBeforeFadeout(offsetBeforeFadeout), m_nextStep(fadeOutTime), m_stepTime(
			fadeOutTime), m_removeTextOnAnimationComplete(removeTextOnAnimationComplete) {
	}

	// the animation will be removed, if false is returned here
	bool step(const float deltaT);

private:
	TextVisual * m_visual;
	float m_offsetBeforeFadeout;
	float m_nextStep;
	float m_stepTime;
	bool m_removeTextOnAnimationComplete;
};
