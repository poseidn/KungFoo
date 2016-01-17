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

#include <array>
#include <cassert>

template<class TType, size_t TSize>
class RingBuffer {
public:
	RingBuffer() :
			m_currentPosition(0), m_currentSize(0) {
	}

	void push(TType const & t) {
		m_currentPosition++;
		handleCurrentPositionWrapAround();
		m_buffer[m_currentPosition] = t;
		if (m_currentSize < m_buffer.size())
			m_currentSize++;
	}

	// get the most recent entries with get(0)
	// or the ones before with get ( -n )
	// todo: put this in one
	TType & get(int entry) {
		int itemNumber = m_currentPosition + entry;

		while (itemNumber < 0)
			itemNumber += TSize;

		itemNumber = itemNumber % TSize;
		return m_buffer[itemNumber];
	}

	TType const& get(int entry) const {
		int itemNumber = m_currentPosition + entry;

		while (itemNumber < 0)
			itemNumber += TSize;

		itemNumber = itemNumber % TSize;
		return m_buffer[itemNumber];
	}

	// call this only, if you made sure there are actually entries in the buffer
	TType const& last() const {
		assert(size() > 0);
		return get(0);
	}

	// size can be < TSize if no items have been added, but is never bigger then
	// TSize
	size_t size() const {
		return m_currentSize;
	}

	int smallestIndex() const {
		// not really true, but the only way to return something useful
		if (size() == 0)
			return 0;

		return -int(size() - 1);
	}

	bool hasEntries() const {
		return size() > 0;
	}

	void clear() {
		m_buffer.clear();
		m_currentSize = 0;
	}

private:

	void handleCurrentPositionWrapAround() {
		if (m_currentPosition >= TSize) {
			m_currentPosition = 0;
		}
	}

	std::array<TType, TSize> m_buffer;
	size_t m_currentPosition;
	size_t m_currentSize;
};

