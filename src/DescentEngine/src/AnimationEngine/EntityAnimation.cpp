#include "EntityAnimation.h"

#include "../EntityEngine/Entity.h"
#include "../Visuals/SpriteVisual.h"

TransformLocation::TransformLocation(Vector2 initialPosition, Vector2 finalLocation, float duration) :
		m_wasSetToInitial(false), m_initialPosition(initialPosition), m_finalLocation(finalLocation), m_duration(
				duration) {

	m_movePerTime = m_finalLocation - m_initialPosition;
	m_movePerTime = m_movePerTime / duration;
}

void TransformLocation::transform(float deltaT, Entity & ent) {
	if (!m_wasSetToInitial) {
		ent.setMoveIntent(m_initialPosition);
		m_wasSetToInitial = true;
	}
	const Vector2 movePart(m_movePerTime * deltaT);
	ent.deltaMoveIntent(movePart);
}

float TransformLocation::getDuration() const {
	return m_duration;
}

TransformTransparency::TransformTransparency(float initialT, float finalT, float duration) :
		m_initialT(initialT), m_finalT(finalT), m_duration(duration), m_wasSetToInitial(false) {

	m_movePerTime = m_finalT - m_initialT;
	m_movePerTime = m_movePerTime / duration;
}

void TransformTransparency::transform(float deltaT, Entity & ent) {
	if (!m_wasSetToInitial) {
		ent.getActiveVisual().get().setTransparency(m_initialT);
		m_wasSetToInitial = true;
	}

	const float movePart(m_movePerTime * deltaT);
	ent.getActiveVisual().get().setTransparency(ent.getActiveVisual().get().getTransparency() + movePart);
}

float TransformTransparency::getDuration() const {
	return m_duration;
}
