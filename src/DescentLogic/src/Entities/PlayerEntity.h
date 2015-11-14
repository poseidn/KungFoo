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

