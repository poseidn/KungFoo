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
