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

#include "InputRecordType.h"

namespace special_move {

class Deactivator {
public:
	Deactivator(InputRecordType & record) :
			m_record(record) {
	}

	void registerIndex(int index) {
		if (index < m_record.smallestIndex()) {
			logging::Fatal() << "Index " << index << " does not exist in ring buffer";
			return;
		}

		m_indices.push(index);
	}

	void invalidate() {
		while (!m_indices.empty()) {
			int i = m_indices.top();
			m_record.get(i).Used = true;
			m_indices.pop();
		}
	}

	size_t indexSize() const {
		return m_indices.size();
	}

private:
	std::stack<int> m_indices;
	InputRecordType & m_record;

};
}
