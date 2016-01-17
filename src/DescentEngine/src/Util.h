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

#include "VectorTypes.h"
#include "Cpp11.h"

#include <utility>
#include <cassert>
#include <cmath>
#include <map>
#include <memory>
#include <functional>

#include <boost/range/irange.hpp>

namespace std14 {

template<class T, class ... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	return std::unique_ptr < T > (new T(std::forward<Args>(args)...));
}

}

template<class T> using uniq = std::unique_ptr<T>;

template<class TIt, class TItem>
TIt find_uniq(TIt first, TIt last, TItem * ptr) {
	return std::find_if(first, last, [ptr]( uniq<TItem> & item ) {return item.get() == ptr;});
}

namespace util {

template<class TCollection>
void erase_if(TCollection & coll,
		std::function<bool(typename TCollection::value_type &)> selection_lambda) {
	auto it = std::remove_if(coll.begin(), coll.end(), selection_lambda);
	// delete all elements from the first one to delete to the very end of the list
	coll.erase(it, coll.end());
}

template<class TVal>
class ValidValue {
public:
	ValidValue() {
	}

	ValidValue(TVal const& v) :
			m_isValid(true), m_value(v) {
	}

	void setValue(TVal const& v) {
		m_value = v;
		m_isValid = true;
	}

	TVal const& getValue() const {
		// one should never ask for an invalid value
		assert(isValid());
		return m_value;
	}

	void invalidate() {
		m_isValid = false;
	}

	bool isValid() const {
		return m_isValid;
	}

	ValidValue<TVal> & operator=(TVal const& other) {
		setValue(other);
		// by convention, always return *this
		return *this;
	}

private:
	bool m_isValid = false;
	TVal m_value;
};

/* class to run a certain computation only once and always return the result
 *
 * 		auto lmbDirection = [&pent, &gs] () -> float {
 constexpr float maxDirection = 0.9f;

 // compute player location
 float direction = pent->getPosition().x()
 / gs.getEngines().renderEngine().getScreenTransform().screenSizeInTiles().x();
 // shift to -0.7 to 0.7
 direction = (direction * maxDirection * 2.0f) - maxDirection;
 return direction;
 };

 util::RunOnce<decltype( lmbDirection), float> direction(lmbDirection);
 */

// todo: get the return type from the std::function object
template<class TLambda, class TResult>
class RunOnce {
public:
	RunOnce(TLambda const lmb) :
			m_lmb(lmb), m_res(), m_wasRun(false) {

	}

	TResult result() {
		if (m_wasRun)
			return m_res;

		m_res = m_lmb();
		m_wasRun = true;

		return m_res;
	}

private:
	TLambda m_lmb;
	TResult m_res;
	bool m_wasRun;
};

template<class TKey, class TVal>
inline bool initMap(std::map<TKey, TVal> & m, TKey const& k) {
	auto it = m.find(k);
	if (it == m.end()) {
		// add it !
		m[k] = TVal();
		return true;
	}

	return false;
}

template<class TFloatType>
inline bool withinDelta(TFloatType const& valMust, TFloatType const& val, TFloatType const& delta) {
	return (std::abs(valMust - val) < delta);
}

inline bool withinDelta(Vector2 const& valMust, Vector2 const& val, float const& deltaSquared) {
	const float dist = (valMust - val).magSquared();
	return dist < deltaSquared;
}

CPP11_CONSTEXPR_OPTIONAL inline float sq(float f1) {
	return f1 * f1;
}

}

