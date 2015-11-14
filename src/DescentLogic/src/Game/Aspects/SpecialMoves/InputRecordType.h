#pragma once

#include "DescentEngine/src/DataTypes/RingBuffer.h"
#include "InputItem.h"

namespace special_move {

typedef RingBuffer<InputItem, 8> InputRecordType;

}
