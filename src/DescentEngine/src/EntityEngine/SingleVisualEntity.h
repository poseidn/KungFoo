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

#include <memory>
#include <vector>
#include "Entity.h"

#include "../Engines.h"

#include "../TextureSet.h"
#include "../Visuals/LayerPriority.h"

//#include "MoveAccessClass.h"
//class MoveAccessClass

// maybe use the Collection SoA here, also to be in shape for
// OpenGL ES Vertex Arrays

// pointer to customs behaviour classes for specialized draw / quantities

// TODO: who deletes this visual ?
class SingleVisualEntity: public Entity {
public:
	SingleVisualEntity(Vector2 initialPosition, Rectangle2 boundingBox, SpriteVisualRef visual) :
			Entity(initialPosition, boundingBox), m_visual(visual) {
		setActiveVisual(m_visual);
	}

	virtual ~SingleVisualEntity() {
	}

	// might remove the "final" if needed at some point
	void unregister(Engines & eg) CPP11_OVERRIDE {
		Entity::unregister(eg);
		// todo: are we sure this visual has been added to the render engine ?
		// we dont do it ourself, maybe move this code here
		// will also delete the C++ object once it was been taken out of the render chain
		eg.renderEngine().removeSpriteVisual(m_visual, true);
	}

	SpriteVisualRef getVisual() {
		return m_visual;
	}

private:
	SpriteVisualRef m_visual;
};

