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

class EnemyEntity: public FighterEntity {
public:
	EnemyEntity(Vector2 intialPosition, Rectangle2 boundingBox) :
			FighterEntity(intialPosition, boundingBox), m_isAttacking(false) {
	}

	virtual ~EnemyEntity() {
	}

	void startAttack() {
		m_isAttacking = true;
	}

	void stopAttack() {
		m_isAttacking = false;
	}

	bool isAttacking() const {
		return m_isAttacking;
	}

	virtual float getMaxSpeed() const {
		return EnemyBehaviour::MaxSpeed;
	}

private:
	bool m_isAttacking;
};

class EnemyFatEntity CPP11_FINAL : public EnemyEntity {
public:
	EnemyFatEntity(Vector2 intialPosition, Rectangle2 boundingBox) :
			EnemyEntity(intialPosition, boundingBox) {
		m_life = EnemyFatBehaviour::Life;
	}

	virtual ~EnemyFatEntity() {
	}

	virtual float getMaxSpeed() const CPP11_OVERRIDE {
		return EnemyFatBehaviour::MaxSpeed;
	}

	// this one is reallly fat !
	virtual float getMass() const CPP11_OVERRIDE {
		return 10.0f;
	}
};
