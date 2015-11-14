#pragma once

#include <utility>
#include <iostream>
#include <cmath>

#include "Cpp11.h"

template<class T>
class VectorX {
public:
	VectorX(T x) :
			m_x(x) {
	}

	T x() const {
		return m_x;
	}
	void setX(T v) {
		m_x = v;
	}
protected:
	T m_x;
};

template<class T>
class VectorY {
public:
	VectorY(T y) :
			m_y(y) {
	}

	T y() const {
		return m_y;
	}

	void setY(T v) {
		m_y = v;
	}
protected:
	T m_y;
};

template<class T>
class VectorZ {
public:
	VectorZ(T z) :
			m_z(z) {
	}

	T z() const {
		return m_z;
	}
	void setZ(T v) {
		m_z = v;
	}
protected:
	T m_z;
};

template<class T>
class Vector3Base: public VectorX<T>, public VectorY<T>, public VectorZ<T> {
public:
	Vector3Base(T x, T y, T z) :
			VectorX<T>(x), VectorY<T>(y), VectorZ<T>(z) {
	}

	Vector3Base() :
			VectorX<T>(0), VectorY<T>(0), VectorZ<T>(0) {

	}
};

typedef Vector3Base<float> Vector3;

class Vector2Uint: public VectorX<size_t>, public VectorY<size_t> {
public:
	CPP11_CONSTEXPR_OPTIONAL
	Vector2Uint() :
			VectorX<size_t>(0), VectorY<size_t>(0) {

	}

	CPP11_CONSTEXPR_OPTIONAL
	Vector2Uint(size_t x, size_t y) :
			VectorX<size_t>(x), VectorY<size_t>(y) {

	}
};

class Vector2: public VectorX<float>, public VectorY<float> {
public:
	CPP11_CONSTEXPR_OPTIONAL
	Vector2() :
			VectorX<float>(0.0f), VectorY<float>(0.0f) {

	}

	CPP11_CONSTEXPR_OPTIONAL
	Vector2(float x, float y) :
			VectorX<float>(x), VectorY<float>(y) {

	}

	static CPP11_CONSTEXPR_OPTIONAL Vector2 Unit() {
		return Vector2(1.0f, 1.0f);
	}

	static CPP11_CONSTEXPR_OPTIONAL Vector2 UnitX() {
		return Vector2(1.0f, 0.0f);
	}

	static CPP11_CONSTEXPR_OPTIONAL Vector2 UnitY() {
		return Vector2(0.0f, 1.0f);
	}

	static CPP11_CONSTEXPR_OPTIONAL Vector2 Zero() {
		return Vector2(0.0f, 0.0f);
	}

	static float angleBetween(Vector2 const& v1, Vector2 const& v2) {
		auto mul = v1 * v2;
		auto mag = v1.mag() * v2.mag();
		return acos(mul / mag);
	}

	// be careful, as this method only checks for a veeeery small magnitude, but not for exactly zero
	bool nonZero() const {
		return magSquared() > 0.000000001f;
	}

	void alignAlongX() {
		if (x() > 0)
			setX(mag());
		else
			setX(-mag());
		setY(0);
	}

	void alignAlongY() {
		if (y() > 0)
			setY(mag());
		else
			setY(-mag());
		setX(0);
	}

	Vector2 rotatePiHalfClockwiseCopy() const {
		return Vector2(y(), -x());
	}

// todo: optimize the instatiation of all this vector objects here
	Vector2 operator+(Vector2 const& other) const {
		const Vector2 newVec(this->x() + other.x(), this->y() + other.y());
		return newVec;
	}

	Vector2 operator-(Vector2 const& other) const {
		const Vector2 newVec(this->x() - other.x(), this->y() - other.y());
		return newVec;
	}

	Vector2 operator-() const {
		const Vector2 newVec(-this->x(), -this->y());
		return newVec;
	}

	Vector2 operator*(float factor) const {
		const Vector2 newVec(this->x() * factor, this->y() * factor);
		return newVec;
	}

	float operator*(Vector2 const& v) const {
		return this->x() * v.x() + this->y() * v.y();
	}

	Vector2 operator/(float div) const {
		const Vector2 newVec(this->x() / div, this->y() / div);
		return newVec;
	}

	Vector2 & operator=(Vector2 const& other) {
		this->setX(other.x());
		this->setY(other.y());
		return *this;
	}

	bool operator==(Vector2 const& other) const {
		return (this->x() == other.x()) && (this->y() == other.y());
	}

	float magSquared() const {
		return x() * x() + y() * y();
	}

	float mag() const {
		return sqrt(magSquared());
	}

	Vector2 normalizedCopy() const {
		const float myMag = this->mag();

		if (myMag == 0.0f) {
			return Zero();
		} else {
			const float norm = 1.0f / myMag;
			const Vector2 newVec(norm * this->x(), norm * this->y());
			return newVec;
		}
	}

// performs a copy of the vector and limits the maximum magnitude
	Vector2 limitedCopy(const float maxMagnitude) const {
		const float myMag = mag();
		float reductionFactor;

		if (myMag > maxMagnitude) {
			reductionFactor = maxMagnitude / myMag;
		} else {
			reductionFactor = 1.0f;
		}
		return (*this) * reductionFactor;
	}

	template<class TListType>
	void addToList(TListType & l) const {
		l.push_back(x());
		l.push_back(y());
	}
};

inline std::ostream& operator<<(std::ostream& os, Vector2 const& v) {
	os << "(" << v.x() << "|" << v.y() << ")";
	return os;
}
// first:  offset from origin
// second: direction ( not normalized in all cases )
typedef std::pair<Vector2, Vector2> Line2d;

class VectorSupport {
public:
	static std::pair<bool, Vector2> intersectLines(Line2d a, Line2d b) {
		float numerator = ((b.first.y() - a.first.y()) * a.second.x())
				+ ((a.first.x() - b.first.x()) * a.second.y());
		float denominator = (b.second.x() * a.second.y()) - (b.second.y() * a.second.x());

		if (std::fabs(denominator) < VeeeeerySmall)
			return std::pair<bool, Vector2>(false, Vector2::UnitX());

		float t2 = numerator / denominator;

		Vector2 intersection = b.first + b.second * t2;

		return std::pair<bool, Vector2>(true, intersection);
	}

private:
	static CPP11_CONSTEXPR float VeeeeerySmall;

};

