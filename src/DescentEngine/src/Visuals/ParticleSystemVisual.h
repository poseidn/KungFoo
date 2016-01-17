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

#include <vector>
#include <array>
#include <boost/noncopyable.hpp>
#include <boost/math/constants/constants.hpp>

#include "../OpenGLInclude.h"
#include "../VectorTypes.h"
#include "ScreenTransform.h"
#include "LayerPriority.h"
#include "VisualBase.h"

class RandomEngine;

typedef std::array<GLfloat, 4> ColorSpec;
typedef std::vector<ColorSpec> ColorSpecs;

class ParticleSphere {
public:

	ParticleSphere(Vector2 origin, float baseSpeed, RandomEngine & re, float variation = 0.0f,
			float variationXy = 0.0f);

	void init(std::vector<Vector2> & loc, std::vector<Vector2> & vel, ColorSpecs & col) const;

private:
	Vector2 m_origin;
	float m_baseSpeed;
	RandomEngine & m_re;
	float m_variation;
	float m_variationXy;
};

class ParticleStream {
public:

	typedef std::pair<float, float> ColorVariation;
	typedef std::array<ColorVariation, 4> ColorVariations;

	ParticleStream(Vector2 origin, Vector2 direction, float baseSpeed, RandomEngine & re, float variation,
			float variationXy, ColorVariations volVar);

	void init(std::vector<Vector2> & loc, std::vector<Vector2> & vel, ColorSpecs & col) const;

private:
	Vector2 m_origin;
	Vector2 m_direction;
	float m_baseSpeed;
	RandomEngine & m_re;
	float m_variation;
	float m_variationXy;
	ColorVariations m_variationColor;
};

class ParticleSystemVisual: public VisualBase {
public:

	// TODO: use a struct to hold all the particle data
	typedef std::vector<GLfloat> VertexBufferArray;
	typedef std::vector<GLfloat> ColorBufferArray;

	template<class TParticleInitializer>
	ParticleSystemVisual(ScreenTransform const& trans, size_t particleCount, float runtime,
			TParticleInitializer & partInit) :
			m_trans(trans), m_vertices(particleCount * 3, 0.0f), m_color(particleCount * 4, 0.0f), m_verticesVelo(
					particleCount), m_verticesLocation(particleCount), m_verticesExecute(particleCount), m_verticesColor(
					particleCount), m_runtime(runtime), m_pointSize(10.0f) {

		update(trans);
		partInit.init(m_verticesLocation, m_verticesVelo, m_verticesColor);
	}

	size_t getParticleCount() const {
		return m_vertices.size() / 3;
	}

	GLfloat getPointSize() const {
		return m_pointSize;
	}

	GLfloat const* getColorBufferPtr() const {
		return &m_color.front();
	}

	GLfloat const* getVertexBufferPtr() const {
		return &m_vertices.front();
	}

	bool isRunning() const {
		return m_runtime > 0.0f;
	}

	void update(ScreenTransform const& trans);

	// we need to store this, becaue the vertices will be computed outside of the
	//
	ScreenTransform const& m_trans;
	VertexBufferArray m_vertices;
	ColorBufferArray m_color;
	std::vector<Vector2> m_verticesVelo;
	std::vector<Vector2> m_verticesLocation;
	std::vector<float> m_verticesExecute;
	ColorSpecs m_verticesColor;

	float m_runtime;

	GLfloat m_pointSize;
};

