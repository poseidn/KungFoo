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

