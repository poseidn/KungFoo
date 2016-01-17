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

#include "ParticleSystemVisual.h"

#include "../RandomEngine.h"

/*
 ParticleSystemVisual::ParticleSystemVisual(ScreenTransform const& trans, size_t particleCount,
 Vector2 const& origin, Vector2 const& spreadDirection) :
 m_trans(trans), m_vertices(particleCount * 3, 0.0f), m_verticesVelo(particleCount), m_verticesLocation(
 particleCount, origin), m_origin(origin), m_pointSize(10.0f) {
 //update(trans, intialPosition);
 //m_irt
 m_color[0] = 1.0f;
 m_color[1] = 0.0f;
 m_color[2] = 0.0f;
 m_color[3] = 1.0f;

 update(trans);


 for (size_t i = 0; i < m_verticesVelo.size(); i += 1) {
 const float ratio =   2.0f * M_PI * float(i) / float(m_verticesVelo.size());
 const float x = sin(ratio);
 const float y = cos(ratio);
 m_verticesVelo[i] = Vector2(x, y);
 //		m_verticesVelo[i + 1] = y;
 //std::cout << x << " : " << y << std::endl;
 }

 }*/

void ParticleSystemVisual::update(ScreenTransform const& trans) {

	// todo: this is tricky to do with the
	// deferredc lambda concept, because the lambda would
	// need to contain big buffers ...

	size_t i = 0;
	for (Vector2 const& loc : m_verticesLocation) {

		const Vector3 in(loc.x(), loc.y(), 0.9f);
		const Vector3 toScreen(trans.vectorToScreen(in));
		m_vertices[i] = toScreen.x();
		// use a minus here so there y coord from the user is always positive
		m_vertices[i + 1] = -toScreen.y();
		m_vertices[i + 2] = toScreen.z();
		i += 3;
	}

	i = 0;
	for (auto const& col : m_verticesColor) {
		for (size_t j = 0; j < 4; j++) {
			m_color[i] = col[j];
			i++;
		}
	}

}

ParticleSphere::ParticleSphere(Vector2 origin, float baseSpeed, RandomEngine & re, float variation,
		float variationXy) :
		m_origin(origin), m_baseSpeed(baseSpeed), m_re(re), m_variation(variation), m_variationXy(variationXy) {
}

void ParticleSphere::init(std::vector<Vector2> & loc, std::vector<Vector2> & vel, ColorSpecs & col) const {
	for (Vector2 & l : loc) {
		l = m_origin;
	}

	const float pi = boost::math::constants::pi<float>();

	for (size_t i = 0; i < vel.size(); i += 1) {
		const float ratio = 2.0f * pi * float(i) / float(vel.size());

		const float var = m_re.randomFloat(RandomEngine::SpanFloat(-m_variation, m_variation));
		const float varXy = 1.0f + m_re.randomFloat(RandomEngine::SpanFloat(-m_variationXy, m_variationXy));

		const float x = sin(ratio) * varXy;
		const float y = cos(ratio) * varXy;

		vel[i] = Vector2(x, y) * (1.0f + var) * m_baseSpeed;
	}
}

ParticleStream::ParticleStream(Vector2 origin, Vector2 direction, float baseSpeed, RandomEngine & re,
		float variation = 0.0f, float variationXy = 0.0f, ColorVariations colVar = { { { 1.0f, 1.0f }, { 1.0f,
				1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f } } }) :
		m_origin(origin), m_direction(direction), m_baseSpeed(baseSpeed), m_re(re), m_variation(variation), m_variationXy(
				variationXy), m_variationColor(colVar) {
}

void ParticleStream::init(std::vector<Vector2> & loc, std::vector<Vector2> & vel, ColorSpecs & col) const {
	for (Vector2 & l : loc) {
		l = m_origin;
	}

	const float pi = boost::math::constants::pi<float>();

	for (size_t i = 0; i < vel.size(); i += 1) {
		const float ratio = 2.0f * pi * float(i) / float(vel.size());

		const float var = m_re.randomFloat(RandomEngine::SpanFloat(-m_variation, m_variation));
		const float varX = m_re.randomFloat(RandomEngine::SpanFloat(-m_variationXy, m_variationXy));
		const float varY = m_re.randomFloat(RandomEngine::SpanFloat(-m_variationXy, m_variationXy));

		const float x = m_direction.x() + varX;
		const float y = m_direction.y() + varY;

		vel[i] = Vector2(x, y) * (1.0f + var) * m_baseSpeed;

		for (size_t j = 0; j < 4; j++) {
			const float R = m_re.randomFloat(
					RandomEngine::SpanFloat(m_variationColor[j].first, m_variationColor[j].second));
			col[i][j] = R;
		}
	}
}
