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

