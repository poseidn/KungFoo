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

