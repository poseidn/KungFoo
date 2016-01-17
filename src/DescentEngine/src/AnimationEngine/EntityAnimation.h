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
#include <utility>
#include <boost/noncopyable.hpp>
#include "../Cpp11.h"
#include "../VectorTypes.h"

class Entity;

typedef float AnimationTimecode;

class EntityAnimationBase: boost::noncopyable {
public:
	virtual void step(const float deltaT) = 0;
	virtual bool decreaseDuration(AnimationTimecode deltaT) = 0;
};

// todo: use a dedicated extrapolation class to have linear / exp etc.
class TransformLocation CPP11_FINAL {
public:
	TransformLocation(Vector2 initialPosition, Vector2 finalLocation, float duration);

	void transform(float deltaT, Entity & ent);

	float getDuration() const;

private:
	bool m_wasSetToInitial;
	const Vector2 m_initialPosition;
	const Vector2 m_finalLocation;
	Vector2 m_movePerTime;
	const float m_duration;
};

class TransformTransparency CPP11_FINAL  {
public:
	TransformTransparency(float initialT, float finalT, float duration);

	void transform(float deltaT, Entity & ent);

	float getDuration() const;

private:
	const float m_initialT;
	const float m_finalT;
	float m_movePerTime;
	const float m_duration;
	bool m_wasSetToInitial;
};

// can we have multiple transform via variadic templates here ?? whoop whoop !
template<class TTransform>
class EntityAnimation: public EntityAnimationBase {
public:
	virtual ~EntityAnimation() = default;

	EntityAnimation(Entity & ent, TTransform const& trans) :
			m_ent(ent), m_trans(trans), m_duration(trans.getDuration()) {
	}

	virtual void step(const float deltaT) CPP11_OVERRIDE {
		m_trans.transform(deltaT, m_ent);
	}

	AnimationTimecode getDuration() const {
		return m_duration;
	}

	virtual bool decreaseDuration(AnimationTimecode deltaT) CPP11_OVERRIDE {
		m_duration -= deltaT;

		return (m_duration > 0.0f);
	}

private:
	Entity & m_ent;
	TTransform m_trans;
	AnimationTimecode m_duration;
};
