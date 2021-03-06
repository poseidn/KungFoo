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

#include <algorithm>
#include <boost/noncopyable.hpp>

class VisualBase {
public:
	VisualBase() :
			m_visible(true), m_toRemove(false), m_isIngame(true), m_animated(false), m_transparency(1.0f), m_sizeScale(
					1.0f) {
	}

	virtual ~VisualBase() = default;

	void setVisible(bool visible) {
		m_visible = visible;
	}

	bool getVisible() const {
		return m_visible;
	}

	void setTransparency(float t) {
		m_transparency = t;
		//std::max((unsigned char) (t * 255.0), (unsigned char) 255);
	}

	float getTransparency() const {
		return m_transparency; //	return m_transparency * 0.00392156862745098f;
	}

	bool toRemove() const {
		return m_toRemove;
	}
	void setToRemove() {
		m_toRemove = true;
	}

	// where 1.0f is the regular size
	// todo : range is a bit limited ... use another transformation
	void setSizeScale(float s) {
		m_sizeScale = s;
	}

	float getSizeScale() const {
		return m_sizeScale;	// 1.0f;	//return float(m_sizeScale) * 0.0078125; //= 1/128.0
	}

	// update the internal buffers of OpenGL
	// in fact, it returns a lambda expression which can be
	// executed by the render engine at the best possible time
	//void update(ScreenTransform const& trans, Vector2 const& pos) = 0;

protected:
	bool m_visible;
	bool m_toRemove;

	bool m_isIngame;
	bool m_animated;

	float m_transparency;
	float m_sizeScale;

};
