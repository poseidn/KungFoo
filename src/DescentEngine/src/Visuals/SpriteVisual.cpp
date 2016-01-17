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

#include "SpriteVisual.h"

#include "../RenderEngine.h"
#include "../Texture.h"
#include "ScreenTransform.h"

const SpriteVisual::TextureCoordsArray SpriteVisual::m_defaultTextureCoords = { 0, 0, 1, 0, 1, 1, 0, 1 };

const SpriteVisual::TextureCoordsArray4Frames SpriteVisual::m_defaultTextureCoords4Frames = { { 0, 0, 1, 0, 1,
		0.25, 0, 0.25 }, { 0, 0.25, 1, 0.25, 1, 0.5, 0, 0.5 }, { 0, 0.50, 1, 0.50, 1, 0.75, 0, 0.75 }, { 0,
		0.75, 1, 0.75, 1, 1.0, 0, 1.0 } };

const SpriteVisual::TextureCoordsArray8Frames SpriteVisual::m_defaultTextureCoords8Frames = { { 0, 0.0f / 8.0f,
		1, 0.0f / 8.0f, 1, 1.0f / 8.0f, 0, 1.0f / 8.0f, }, { 0, 1.0f / 8.0f, 1, 1.0f / 8.0f, 1, 2.0f / 8.0f, 0,
		2.0f / 8.0f, }, { 0, 2.0f / 8.0f, 1, 2.0f / 8.0f, 1, 3.0f / 8.0f, 0, 3.0f / 8.0f, }, { 0, 3.0f / 8.0f,
		1, 3.0f / 8.0f, 1, 4.0f / 8.0f, 0, 4.0f / 8.0f, }, { 0, 4.0f / 8.0f, 1, 4.0f / 8.0f, 1, 5.0f / 8.0f, 0,
		5.0f / 8.0f, }, { 0, 5.0f / 8.0f, 1, 5.0f / 8.0f, 1, 6.0f / 8.0f, 0, 6.0f / 8.0f, }, { 0, 6.0f / 8.0f,
		1, 6.0f / 8.0f, 1, 7.0f / 8.0f, 0, 7.0f / 8.0f, }, { 0, 7.0f / 8.0f, 1, 7.0f / 8.0f, 1, 8.0f / 8.0f, 0,
		8.0f / 8.0f, } };

// normals for each vertex needed
const SpriteVisual::NormalBufferArray SpriteVisual::m_defaultNormalBuffer = { 0, 0, 1.0f, 0, 0, 1.0f, 0, 0,
		1.0f, 0, 0, 1.0f };

// todo: fix this in MT mode
void SpriteVisual::nextFrame() {
	if (size_t(m_currentFrame + 1) == getTexture()->getAnimationFrames())
		m_currentFrame = 0;
	else
		m_currentFrame++;
}

void SpriteVisual::step(float deltaT) {
	if (!m_animated)
		return;

	m_nextStep -= deltaT;

	if (m_nextStep < 0.0f) {
		m_nextStep = m_stepTime;
		nextFrame();
	}
}

DeferredVisualUpdate SpriteVisual::update(ScreenTransform const& trans, Vector2 const& pos) {
	const float sizeScale = getSizeScale();
	float upperX = pos.x() - m_size.x() * 0.5f * sizeScale;
	float upperY = pos.y() - m_size.y() * 0.5f * sizeScale;

	float lowerX = pos.x() + m_size.x() * 0.5f * sizeScale;
	float lowerY = pos.y() + m_size.y() * 0.5f * sizeScale;

	trans.quadToScreen(upperX, upperY, lowerX, lowerY, isIngame());
	// first vertex of first trig

	// todo: can also be computed once and stored with the visual, or percompute the 1 / max
	// * 1.2f because we want a 20 percent buffer, because 1.0 is "reserved" for gui objects and text
	const float zVal = LayerTools::computeZ(getPriority());

	//VertexBufferArray * vtxBuffer = &m_vertexBuffer;

	// can be executed on the render thread, if needed
	auto lmdUpdate = [ upperX, upperY, lowerX, lowerY, zVal ] ( VisualBase * vb )
	{
		SpriteVisual * sv = static_cast<SpriteVisual *> ( vb );

		sv->m_vertexBuffer[0] = upperX;
		sv->m_vertexBuffer[1] = -lowerY;
		sv->m_vertexBuffer[2] = zVal;
		// second vertex of first trig
			sv->m_vertexBuffer[3] = lowerX;
			sv->m_vertexBuffer[4] = -lowerY;
			sv->m_vertexBuffer[5] = zVal;
			// third vertex of first trig
			sv->m_vertexBuffer[6] = lowerX;
			sv->m_vertexBuffer[7] = -upperY;
			sv->m_vertexBuffer[8] = zVal;
			// first ( and only ) vertex of second trig
			sv->m_vertexBuffer[9] = upperX;
			sv->m_vertexBuffer[10] = -upperY;
			sv->m_vertexBuffer[11] = zVal;
		};

	lmdUpdate(this);

	return lmdUpdate;
}

SpriteVisual::SpriteVisual(ScreenTransform const& trans, TexturePtr tex, Vector2 const& intialPosition,
		Vector2 const& size, LayerPriority prio) :
		VisualBase(), m_textureRef(tex), m_size(size), m_currentFrame(0), m_priority(prio) {
	update(trans, intialPosition);
}

// todo: make this more generic and for all number of textures
GLfloat const * SpriteVisual::getDefaultTextureCoordsPtr() const {
	if (m_textureRef->getAnimationFrames() == 4)
		return m_defaultTextureCoords4Frames[m_currentFrame];
	else if (m_textureRef->getAnimationFrames() == 8)
		return m_defaultTextureCoords8Frames[m_currentFrame];
	else
		return m_defaultTextureCoords;
}

