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

#include <iterator>
#include <cassert>
#include <algorithm>
#include <vector>

template<class TType>
class StaticList {
public:
	StaticList() {
	}

	class StaticListRef {
	public:
		friend StaticList;

		// this will only generate in invalid state
		StaticListRef() {
		}

		TType const& get() const {
			return *m_ptr;
		}

		TType & get() {
			return *m_ptr;
		}

		bool isValid() const {
			return m_ptr != nullptr;
		}

	protected:
		StaticListRef(TType * ptr) :
				m_ptr(ptr) {
		}

		TType * getPtr() const {
			return m_ptr;
		}

	private:
		TType * m_ptr;
	};

	typedef StaticListRef Ref;

private:

public:
	Ref push_back(TType const& t) {
		/*auto firstDisabled = std::find_if(m_vec.begin(), m_vec.end(), []( VectorItem const& it )
		 {
		 return !it.first;
		 });
		 */
		/*if (firstDisabled == m_vec.end()) {
		 // not items are free, add a new one
		 m_vec.push_back(t);
		 return Ref(this, m_vec.size() - 1);
		 } else {
		 // replace the disabled item
		 firstDisabled->first = true;
		 firstDisabled->second = t;
		 return Ref(this, firstDisabled - m_vec.begin());
		 }*/
		auto pt = new TType(t);
		m_vec.push_back(pt);
		return Ref(pt);
	}

	void clear() {
		m_vec.clear();
	}

	void remove(Ref const& r) {
		// disable this one
		assert(false);
	}

	// the next two
	// have bad rt-performance
	// they are just implemented
	// to be inter-changeable with StaticVector
	TType const& get(size_t pos) const {
		/*auto it = std::advance(m_vec.begin(), pos);
		 return *it;*/
		//return *m_vec.begin();
		//return TType();
		return *(*m_vec.begin());

	}

	TType & get(size_t pos) {
		/*auto it = std::advance(m_vec.begin(), pos);
		 return *it;*
		 //return TT
		 * ret
		 */
		return *(*m_vec.begin());
		//return TType();
	}

	size_t activeSize() const {
		return m_vec.size();
	}

	size_t activeCount() const {
		return m_vec.size();
	}

	bool isActive(size_t pos) const {
		//return m_vec[pos].first;
		return true;
	}

	typename std::list<TType *>::iterator begin() {
		return m_vec.begin();
	}

	typename std::list<TType *>::iterator end() {
		return m_vec.end();
	}

private:

	std::list<TType *> m_vec;
};

