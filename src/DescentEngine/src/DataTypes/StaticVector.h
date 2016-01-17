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

#include <cassert>
#include <algorithm>
#include <vector>
#include <memory>
#include <functional>

template<class TType>
class StaticVector {
public:
	~StaticVector() {
		deleteRefs();
	}

	class StaticVectorRef {
	public:
		friend StaticVector;

		// this will only generate in invalid state
		StaticVectorRef() {
		}

		TType const& get() const {
			assert(m_staticVec);
			return m_staticVec->get(m_pos);
		}

		TType & get() {
			assert(m_staticVec);
			return m_staticVec->get(m_pos);
		}

		bool isValid() const {
			return m_staticVec != nullptr;
		}

	protected:
		StaticVectorRef(StaticVector * vec, size_t pos) :
				m_staticVec(vec), m_pos(pos) {
		}

		size_t getPosition() const {
			return m_pos;
		}

		void setPosition(size_t pos) {
			m_pos = pos;
		}

	private:
		StaticVector * m_staticVec = nullptr;
		size_t m_pos = 0;
	};

	typedef StaticVectorRef * InternalRef;

	class RefContainer {
	public:
		RefContainer() {
		}

		RefContainer(InternalRef ptr) :
				m_ptr(ptr) {
		}

		TType & get() {
			return m_ptr->get();
		}

		InternalRef getInternal() const {
			return m_ptr;
		}

		bool isValid() const {
			return (m_ptr != nullptr);
		}

	private:
		InternalRef m_ptr = nullptr;
	};

	typedef RefContainer Ref;

private:

	typedef std::pair<StaticVectorRef *, TType> VectorItem;

public:
	typedef std::function<bool(TType const&)> InsertPointLambda;

	Ref push_back(TType const& t) {
		//return push_back(t, []( TType const& t ) {return false;});
		auto pRef = new StaticVectorRef(this, m_vec.size());
		m_vec.push_back(std::make_pair(pRef, t));
		return Ref(pRef);
	}

	Ref push(TType const& t, InsertPointLambda lmdInsert) {

		size_t insertPoint = 0;
		for (auto const& it : m_vec) {
			if (lmdInsert(it.second))
				break;
			insertPoint++;
		}

		auto pRef = new StaticVectorRef(this, insertPoint);

		// todo: can also be at a middle positions,
		// the index of all following has to be updated in these cases

		m_vec.insert(m_vec.begin() + insertPoint, std::make_pair(pRef, t));
		updateIndexAfter(insertPoint);

		return Ref(pRef);

		/*auto firstDisabled = std::find_if(m_vec.begin(), m_vec.end(), []( VectorItem const& it )
		 {
		 return !it.first;
		 });

		 if (firstDisabled == m_vec.end()) {
		 // not items are free, add a new one
		 m_vec.push_back(std::make_pair(true, t));
		 return Ref(this, m_vec.size() - 1);
		 } else {
		 // replace the disabled item
		 firstDisabled->first = true;
		 firstDisabled->second = t;
		 return Ref(this, firstDisabled - m_vec.begin());
		 }*/

	}

	void clear() {

		deleteRefs();

		m_vec.clear();
	}

	void remove(Ref & r) {
		//m_vec[r.getPosition()].first = false;
		m_vec.erase(m_vec.begin() + r.getInternal()->getPosition());
		updateIndexAfter(r.getInternal()->getPosition());

		delete r.getInternal();
	}

	TType
	const& get(size_t pos) const {
		return m_vec[pos].second;
	}

	TType & get(size_t pos) {
		return m_vec[pos].second;
	}

	size_t activeSize() const {
		return m_vec.size();
	}

	size_t activeCount() const {
		/*return std::count_if(m_vec.begin(), m_vec.end(), []( VectorItem const& vi ) {
		 return vi.first;
		 });*/
		return m_vec.size();
	}

	bool isActive(size_t pos) const {
		//return m_vec[pos].first;
		return true;
	}

private:

	void deleteRefs() {
		for (auto & it : m_vec) {
			delete it.first;
		}
	}

	void updateIndexAfter(size_t forPos) {
		for (size_t i = forPos; i < m_vec.size(); i++) {
			m_vec[i].first->setPosition(i);
		}
	}

	std::vector<VectorItem> m_vec;
};

