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

#include <boost/noncopyable.hpp>
#include "../Texture.h"
#include "../TextureRef.h"
#include "../VectorTypes.h"
#include "ScreenTransform.h"
#include "LayerPriority.h"
#include "VisualBase.h"

#include "LightFactory.h"

class LightVisual: VisualBase {
public:
	LightVisual(ScreenTransform const& trans, LightFactory & factory, Vector2 const& intialPosition) :
			  m_needsUpdate(true), m_lightNumber(GL_LIGHT1) {
		update(trans, intialPosition);
		m_lightNumber = factory.getNextLight();
	}

	void update(ScreenTransform const& trans, Vector2 const& pos) {

		m_position.setX(pos.x());
		m_position.setY(pos.y());
		m_position.setZ(-40.0);

		m_position = trans.vectorToScreen(m_position);

		m_needsUpdate = true;
	}

	LayerPriority getPriority() const {
		return m_priority;
	}

	void reset() {
		m_currentFrame = 0;
	}

	bool getNeedsUpdate() const {
		return m_needsUpdate;
	}

	void setNeedsUpdate(bool upd) {
		m_needsUpdate = upd;
	}

	Vector3 const& getPosition() const {
		return m_position;
	}

	GLenum getLightNumber() const {
		return m_lightNumber;
	}

private:
	bool m_needsUpdate;
	unsigned int m_currentFrame;
	LayerPriority m_priority;
	Vector3 m_position;
	GLenum m_lightNumber;
};

