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
