#pragma once

#include "PatternNodes.h"

namespace special_move {

class InputPattern {
	public:
		typedef std::vector<std::shared_ptr<PatternNodeBase>> PatternItemsVector;
		typedef std::vector<PatternNodeBase *> PatternItemsVectorPtr;

		InputPattern(float maxDuration, PatternItemsVectorPtr const& items) :
				m_overallDuration(maxDuration) {
			// copy the items manually to a shared ptr
			// change the order of the iteration, we will look for the last elements of the sequence first
			for (PatternItemsVectorPtr::const_reverse_iterator revIt = items.rbegin(); revIt != items.rend();
					revIt++) {
				m_items.push_back(std::shared_ptr < PatternNodeBase > (*revIt));
			}
		}

		float getOverallDuration() const {
			return m_overallDuration;
		}

		bool match(InputRecordType & record) {

			if (m_items.size() == 0)
				// nothing to match here
				return false;
			//logging::Info() << "checking with " << m_items.size() << "paterns";

			PatternItemsVector::const_iterator currentItem = m_items.begin();
			bool hasMatched = false;
			int firstInputUsed = 1;
			int lastInputUsed = 1;
			float overallDuration = -1.0f;
			Deactivator deac(record);

			// start with the newest entries first
			for (int i = 0; i >= record.smallestIndex();) {
				// is a shared pointer
				auto patternNode = *currentItem;
				PatternNodeBase::MatchResult matchRes = patternNode->match(record, deac, i,
						record.smallestIndex());

				if (std::get < 0 > (matchRes)) {
					// whoop whoop, this matched !

					if (firstInputUsed > 0) {
						firstInputUsed = std::get < 1 > (matchRes);
					}
					// switch the first item which has not been used in the matching process
					i = std::get < 2 > (matchRes) - 1;

					// did we match all items ?
					currentItem++;
					if (currentItem == m_items.end()) {
						lastInputUsed = std::get < 2 > (matchRes);
						hasMatched = true;
						// disable all the input commands used for this pattern
						deac.invalidate();

						break;
					}
				} else {
					// no match, keep on going ...
					i--;
				}

			}

			if (hasMatched) {
				// count the overall time
				float duration = 0.0f;
				for (int i = firstInputUsed; i >= lastInputUsed; i--) {
					InputItem const& it = record.get(i);
					duration += it.Duration;
				}
				if (duration > getOverallDuration()) {
					//logging::Info() << "Matching failed due to duration, was " << duration << " must be "
					//<< getOverallDuration();

					return false;
				}

				return hasMatched;
			}

			return false;
		}

	private:
		const float m_overallDuration;
		PatternItemsVector m_items;

	};

}
