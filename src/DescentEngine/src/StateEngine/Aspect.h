#pragma once

#include <boost/noncopyable.hpp>

template<class TState>
class Aspect: boost::noncopyable {
public:
	virtual ~Aspect() {
	}

	virtual void init(TState & state) {
	}
};
