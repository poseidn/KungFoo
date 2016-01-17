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

namespace special_move {

class InputItem {
public:
	enum class TypeEnum {
		Undefined, KeyPress, Direction
	};

	enum class DirectionEnum {
		Undefined, Neutral, Up, Down, Left, Right
	};

	enum class KeyPressEnum {
		Undefined, KeyA, KeyB

	};

	InputItem(TypeEnum type = TypeEnum::Undefined, DirectionEnum direction = DirectionEnum::Undefined,
			KeyPressEnum keyPress = KeyPressEnum::Undefined) :
			Duration(0.0f), Type(type), Direction(direction), KeyPress(keyPress), Used(false) {
	}

	InputItem(KeyPressEnum keyPress, float duration = 0.0f) :
			Duration(duration), Type(TypeEnum::KeyPress), Direction(DirectionEnum::Undefined), KeyPress(
					keyPress), Used(false) {
	}

	InputItem(DirectionEnum direction, float duration = 0.0f) :
			Duration(duration), Type(TypeEnum::Direction), Direction(direction), KeyPress(
					KeyPressEnum::Undefined), Used(false) {
	}

	// c++11 delegated constructor for key presses
	// cannot compile for android right now..
	//InputItem(KeyPressEnum keyPress) :
	//		InputItem(TypeEnum::KeyPress, DirectionEnum::Undefined, keyPress) {
	//}

	float Duration;
	TypeEnum Type;
	DirectionEnum Direction;
	KeyPressEnum KeyPress;
	bool Used;

	bool isDefined() const {
		return Type != TypeEnum::Undefined;
	}

	// we don't compare the duration, by design
	bool operator==(InputItem const&other) const {

		bool same = true;

		same = same && (other.Direction == this->Direction);
		same = same && (other.Type == this->Type);
		same = same && (other.KeyPress == this->KeyPress);

		return same;
	}

	bool operator!=(InputItem const&other) const {
		return !this->operator==(other);
	}
};

template < class TRingBuffer >
inline float computeTimeDistance( TRingBuffer const& record, int beginItem, int endItem) {
	float duration = 0.0f;

	assert(beginItem >= endItem);

	// don't add the begin item's time
	for (int i = endItem; i < beginItem; i++) {
		InputItem const& it = record.get(i);
		duration += it.Duration;
	}
	return duration;
}

}

inline std::ostream& operator<<(std::ostream& os, special_move::InputItem const& v) {

	os << "Type: ";
	if (v.Type == special_move::InputItem::TypeEnum::Undefined)
		os << "Undefined ";
	if (v.Type == special_move::InputItem::TypeEnum::Direction)
		os << "Direction ";
	if (v.Type == special_move::InputItem::TypeEnum::KeyPress)
		os << "KeyPress ";

	os << "Direction: ";
	if (v.Direction == special_move::InputItem::DirectionEnum::Undefined)
		os << "Undefined ";
	if (v.Direction == special_move::InputItem::DirectionEnum::Neutral)
		os << "Neutral";
	if (v.Direction == special_move::InputItem::DirectionEnum::Up)
		os << "Up";
	if (v.Direction == special_move::InputItem::DirectionEnum::Down)
		os << "Down";
	if (v.Direction == special_move::InputItem::DirectionEnum::Left)
		os << "Left ";
	if (v.Direction == special_move::InputItem::DirectionEnum::Right)
		os << "Right ";

	os << "Key: ";
	if (v.KeyPress == special_move::InputItem::KeyPressEnum::Undefined)
		os << "Undefined ";
	if (v.KeyPress == special_move::InputItem::KeyPressEnum::KeyA)
		os << "KeyA ";
	if (v.KeyPress == special_move::InputItem::KeyPressEnum::KeyB)
		os << "KeyB ";

	os << " Duration: " << v.Duration;

	return os;
}
