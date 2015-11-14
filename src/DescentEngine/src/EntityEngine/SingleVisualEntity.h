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

