#pragma once

#include "../Log.h"
#include "../VectorTypes.h"

class ScreenTransform {
public:
	ScreenTransform() = default;

	ScreenTransform(ScreenTransform const& st) = default;

	void operator=(ScreenTransform const& st) {
		this->m_tileSizeX = st.m_tileSizeX;
		this->m_tileSizeY = st.m_tileSizeY;

		this->m_tileAmountX = st.m_tileAmountX;
		this->m_tileAmountY = st.m_tileAmountY;

		this->m_screenSize = st.m_screenSize;

		this->m_offset = st.m_offset;
	}

	ScreenTransform(Vector2 tileSize, Vector2 screenSize) :
			m_tileSizeX(tileSize.x()), m_tileSizeY(tileSize.y()), m_tileAmountX(screenSize.x() / tileSize.x()), m_tileAmountY(
					screenSize.y() / tileSize.y()), m_screenSize(screenSize) {

	}

	// the screen-independent corrd-system assumes 1 unit per default tile in x and y direction
	void quadToScreen(float & upperX, float & upperY, float & lowerX, float & lowerY,
			bool useOffset = true) const {
		upperX *= m_tileSizeX;
		lowerX *= m_tileSizeX;

		upperY *= m_tileSizeY;
		lowerY *= m_tileSizeY;

		if (useOffset) {
			upperX += m_offset.x();
			lowerX += m_offset.x();

			upperY += m_offset.y();
			lowerY += m_offset.y();
		}
	}

	Vector3 vectorToScreen(Vector3 const& vec, bool useOffsetX = true, bool useOffsetY = true) const {
		auto v = Vector3(vec.x() * m_tileSizeX, vec.y() * m_tileSizeY, vec.z());
		v.setX((useOffsetX * m_offset.x()) + v.x());
		v.setY((useOffsetY * m_offset.y()) + v.y());

		return v;
	}

	Vector2 vectorToScreen(Vector2 const& vec, bool useOffsetX = true, bool useOffsetY = true) const {
		Vector3 vec3(vec.x(), vec.y(), 0.0f);
		Vector3 vec3Trans = vectorToScreen(vec3, useOffsetX, useOffsetY);

		return Vector2(vec3Trans.x(), vec3Trans.y());
	}

	Vector3 screenToVector(Vector3 const& vecScreen) const {
		Vector3 withOffset;
		withOffset.setX(vecScreen.x() - m_offset.x());
		withOffset.setY(vecScreen.y() - m_offset.y());
		withOffset.setZ(vecScreen.z());

		return Vector3(withOffset.x() / m_tileSizeX, withOffset.y() / m_tileSizeY, withOffset.z());
	}

	Vector2 screenSizeInTiles() const {
		return Vector2(m_tileAmountX, m_tileAmountY);
	}

	Vector2 const& screenSizeInPixel() const {
		return m_screenSize;
	}

	void setOffset(Vector2 const& v) {
		m_offset = v;
	}

	// must be used when ui elements want to have absolute placement on screen
	Vector2 const& getOffset() const {
		return m_offset;
	}
	/*
	 Vector2 const& getOffsetInTiles() const {
	 return m_offset;
	 }*/

	Vector2 const& getScreenSize() const {
		return m_screenSize;
	}

	Vector2 getTileSize() const {
		return Vector2(m_tileSizeX, m_tileSizeY);
	}

private:
	float m_tileSizeX;
	float m_tileSizeY;

	float m_tileAmountX;
	float m_tileAmountY;
	Vector2 m_screenSize;
	Vector2 m_offset;

};
