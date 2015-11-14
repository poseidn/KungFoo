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
