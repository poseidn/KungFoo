#pragma once 

#include <boost/ptr_container/ptr_list.hpp>
#include "Entity.h"

#include "../Engines.h"

#include "../TextureSet.h"
#include "../Visuals/LayerPriority.h"

#include "../AnimationEngine/AnimationEngine.h"
#include "../Visuals/SpriteVisual.h"

//#include "MoveAccessClass.h"
//class MoveAccessClass

// maybe use the Collection SoA here, also to be in shape for
// OpenGL ES Vertex Arrays

// pointer to customs behaviour classes for specialized draw / quantities

// todo: IMPORTTANT: someone has to delete all the animatios in the LoadedVisual struct

// DO NOT PUT THE METHOD DEFINITIONS in the .cpp file !
// otherwise the android compile produces link error, not sure why
// one idea is that overwriting virtual methods across library borders is
// problematic

class MultiVisualEntity: public Entity {
public:
	struct LoadedVisual {
		LoadedVisual(TextureId _id, SpriteVisual _visual) :
				Id(_id), Visual(_visual) {
		}

		TextureId Id;
		SpriteVisual Visual;
	};

	typedef std::vector<LoadedVisual> LoadedVisualList;

	MultiVisualEntity(Vector2 initialPosition, Rectangle2 boundingBox) :
			Entity(initialPosition, boundingBox), m_activeTexture(99966) {
	}

	virtual ~MultiVisualEntity() {
	}

	void addVisual(TextureId id, SpriteVisual pVisual) {
		m_loadedVisuals.push_back( LoadedVisual(id, pVisual));
	}
	/*
	 void changeActiveVisual(Engines & eg, TextureId newActive);
	 void defaultActiveVisual(Engines & eg);
	 */

	void changeActiveVisual(Engines & eg, TextureId newActive) {

		if (m_activeTexture == newActive)
			return;

		if (getActiveVisual().isValid()) {
			// unregister
			eg.renderEngine().removeSpriteVisual(getActiveVisual());
		}

		// find correct visual
		auto it = std::find_if(m_loadedVisuals.begin(), m_loadedVisuals.end(),
				[newActive] ( LoadedVisual const& val )-> bool {return val.Id == newActive;});

		if (it == m_loadedVisuals.end()) {
			logging::Fatal() << "Requested visual not loaded";
		}

		it->Visual.reset();
		auto ref = eg.renderEngine().addSpriteVisual(it->Visual);
		setActiveVisual(ref);

		m_activeTexture = newActive;
	}

	void defaultActiveVisual(Engines & eg) {
		changeActiveVisual(eg, m_loadedVisuals.front().Id);
	}

	void unregister(Engines & eg) CPP11_OVERRIDE
	{
		Entity::unregister(eg);

		// remove all visuals, only one animation will be know to the
		// animation engine, and this one has been deleted above
		if (getActiveVisual().isValid()) {
			eg.renderEngine().removeSpriteVisual(getActiveVisual());
		}
	}

private:
	// todo: refactor, this can be stored global, for the whole game
	// -> no, cannot because each visual has another location !
	LoadedVisualList m_loadedVisuals;

	// for performance reasons
	TextureId m_activeTexture;
};

