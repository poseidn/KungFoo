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

#include "../Engines.h"
#include "../TextureRef.h"
#include "../TextureSet.h"
#include "../VectorTypes.h"
#include "../Rectangle.h"

#include "../RandomEngine.h"
#include "../ResourceEngine/ResourceEngine.h"
#include "../EntityEngine/EntityEngine.h"
#include "../Visuals/SpriteVisual.h"
#include "../Visuals/ParticleSystemVisual.h"
#include "../AnimationEngine/AnimationEngine.h"
#include "../AnimationEngine/ParticleAnimation.h"
#include "../Util.h"

#include "Entity.h"

#include <list>
#include <memory>

class MultiVisualEntity;

class EntityFactory: boost::noncopyable {

public:
	EntityFactory(Engines & eg) :
			m_eg(eg) {
	}

	template<class TEntityType>
	uniq<TEntityType> create(TexturePtr tex, Vector2 initialPosition, Rectangle2 boundingBox, LayerPriority prio =
			LayerPriorityBottom, float animTiming = 0.05f, bool isTransparent = false, float Transparency =
			1.0f) {

		auto pVisual = SpriteVisual(m_eg.renderEngine().getScreenTransform(), tex, initialPosition,
				boundingBox.getSize(), prio);
		pVisual.setTransparency(Transparency);

		if (tex->isAnimated()) {
			pVisual.setAnimated(animTiming);
		}

		//put in front of the render list, because it is fully opaque
		auto spriteRef = m_eg.renderEngine().addSpriteVisual(pVisual);
		return std14::make_unique<TEntityType>(initialPosition, boundingBox, spriteRef);
	}

	//implement jump over table

	template<class TEntityType>
	uniq<TEntityType> createNonVisual(Vector2 const& initialPosition, Rectangle2 const& boundingBox,
			LayerPriority prio = LayerPriorityBottom, bool collidesInJump = false) {
		auto pEnt = std14::make_unique< TEntityType>(initialPosition, boundingBox);
		pEnt->setDoesCollideInJump(collidesInJump);

		return pEnt;
	}

	template<class TEntityType>
	uniq<TEntityType> createMultiVisual(TextureSet & tex, Vector2 initialPosition, Rectangle2 boundingBox,
			Rectangle2 visualSize, LayerPriority prio = LayerPriorityBottom) {
		auto pEnt = std14::make_unique<TEntityType>(initialPosition, boundingBox);

		for (auto const& t : tex) {

			auto pVisual = SpriteVisual(m_eg.renderEngine().getScreenTransform(), t.getTexturePtr(),
					initialPosition, visualSize.getSize(), prio);

			if (t.getTexturePtr()->isAnimated()) {
				pVisual.setAnimated(t.getFrameTiming());
			}

			pEnt->addVisual(t.getId(), pVisual);
		}
		pEnt->defaultActiveVisual(m_eg);

		return pEnt;
	}

	template<class TEntityType>
    uniq<TEntityType> createFromTemplateName(std::string const& templateName, Vector2 initialPosition,
			LayerPriority prio = LayerPriorityBottom) {

		auto & templ = m_eg.entityEngine().getTemplate(templateName);

		TextureSet texSetPlayer;
		for (auto const& it : templ.Textures) {
			auto tex = m_eg.resourceEngine().loadImage(it.getRandomizedFileName(m_eg.randomEngine()),
					it.Frames);
			TextureSetEntry tset(tex, it.Id, it.FrameTiming);
			texSetPlayer.push_back(tset);
		}

		return create<TEntityType>(texSetPlayer.front().getTexturePtr(), initialPosition, templ.BoundingBox,
				templ.VisualPriority, 0.05f, templ.IsTransparent, templ.Transparency);
	}

	template<class TEntityType>
	uniq<TEntityType> createMultiVisual(std::string const& templateName, Vector2 initialPosition,
			LayerPriority prio = LayerPriorityBottom) {

		auto & templ = m_eg.entityEngine().getTemplate(templateName);

		//allow different animation time slices here
		TextureSet texSetPlayer;
		for (auto const& it : templ.Textures) {
			auto tex = m_eg.resourceEngine().loadImage(it.getRandomizedFileName(m_eg.randomEngine()),
					it.Frames);
			TextureSetEntry tset(tex, it.Id, it.FrameTiming);
			texSetPlayer.push_back(tset);
		}

		return createMultiVisual<TEntityType>(texSetPlayer, initialPosition, templ.BoundingBox,
				templ.VisualSize, templ.VisualPriority);
	}

	template<class TEntityType>
	std::list<uniq<TEntityType>> createPunchParticlesTex(Vector2 const& pos, Vector2 const& dir) {
		const float pi = boost::math::constants::pi<float>();

		const float baseSpeed = 15.0f;
		const float cvar = 0.5f;
		const float cvarXy = 0.3f;
		const float varRad = 0.133f;
		const size_t count = (size_t) m_eg.randomEngine().randomInt(RandomEngine::SpanInt(6, 10));

		std::list<uniq<TEntityType>> ents;

		for (size_t i = 0; i < count; i += 1) {

			const float ratio = 2.0f * pi * float(i) / float(count)
					+ m_eg.randomEngine().randomFloat(RandomEngine::SpanFloat(-varRad, varRad));

			const float varVel = m_eg.randomEngine().randomFloat(RandomEngine::SpanFloat(0.2f, cvar));
			/*const float varXy = 1.0f
			 + m_eg.randomEngine().randomFloat(RandomEngine::SpanFloat(-cvarXy, cvarXy));*/

			const float x = sin(ratio); // * varXy;
			const float y = cos(ratio); // * varXy;

			Vector2 vel = Vector2(x, y) * varVel * baseSpeed + dir * 0.2f * baseSpeed; // * (dir + 0.2f);  // * (1.0f + var) * baseSpeed * (dir + 0.2f);

			auto newEnt = createFromTemplateName<TEntityType>(m_eg.randomEngine().randomName("blood", 3),
					pos, LayerPriorityTopMost);

			newEnt->setInitialVelocity(Vector3(vel.x(), vel.y(), 0.0f));
			// scale the visual to have a bit more BLOOOOOOOD !
			auto & vis = newEnt->getVisual().get();
			// look better, when most blood spacles are quite small
			vis.setSizeScale(1.0f + std::fabs(m_eg.randomEngine().randomFloatNormal(0.0f, 1.0f)));
			// blood lives a bit less then 1/2 second
			newEnt->setLimitedPhysicsLifetime(0.44f);
			ents.push_back(std::move(newEnt));
		}

		// have flying tooth
		if (m_eg.randomEngine().randomInt(RandomEngine::SpanInt(0, 6)) == 0) {
			const float toothDir = 4.0f * pi * m_eg.randomEngine().randomFloat();

			const float x = sin(toothDir);
			const float y = cos(toothDir);

			Vector2 vel = Vector2(x, y) * cvar * baseSpeed + dir * 0.2f * baseSpeed; // * (dir + 0.2f);  // * (1.0f + var) * baseSpeed * (dir + 0.2f);
			auto newEnt = createFromTemplateName<TEntityType>("tooth1", pos, LayerPriorityTopMost);
			newEnt->setInitialVelocity(Vector3(vel.x(), vel.y(), 0.0f));
			newEnt->setLimitedPhysicsLifetime(0.94f);
			ents.push_back(std::move(newEnt));
		}

		return ents;
	}

private:
	Engines & m_eg;

};

