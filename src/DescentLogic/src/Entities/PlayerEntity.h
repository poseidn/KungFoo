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

#include <DescentEngine/src/Cpp11.h>
#include "FighterEntity.h"
#include "../Config/PlayerMovement.h"

class PlayerEntity CPP11_FINAL : public FighterEntity {
public:
	PlayerEntity(Vector2 intialPosition, Rectangle2 boundingBox) :
			FighterEntity(intialPosition, boundingBox) {
	}

	virtual ~PlayerEntity() {
	}

	TimeSliceAction & getBikingAction() {
		return m_bikingAction;
	}

	virtual void validateActions(float deltaT, float hitRegenTime) CPP11_OVERRIDE
	{
		getBikingAction().validate(deltaT, PlayerMovement::BikingCooldown);
		FighterEntity::validateActions(deltaT, hitRegenTime);
	}

	virtual void updateVisual(Engines & eg) CPP11_OVERRIDE {
		if (getBikingAction().isActive()) {
			const int sekktor = getCurrentSekktor();
			changeActiveVisual(eg, DescentTextureIds::Biking_0 + sekktor);
		} else {
			FighterEntity::updateVisual(eg);
		}

	}

	// player char will be 10% more heavy than enemies as this will allow
	// the player to push enemies better
	virtual float getMass() const CPP11_OVERRIDE {
		return 1.1f;
	}

private:
	TimeSliceAction m_bikingAction;
};

