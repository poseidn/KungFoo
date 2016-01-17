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

//#include <boost/tr_container/ptr_vector.hpp>
#include <list>
#include <vector>

#include "LayerPriority.h"
#include "../DataTypes/StaticVector.h"
#include "../DataTypes/StaticList.h"

class SpriteVisual;

// todo: maybe faster to use std :: deque here
typedef std::list<SpriteVisual *> SpriteVisualList;
typedef std::vector<SpriteVisual *> SpriteVisualVector;

typedef StaticVector<SpriteVisual> SpriteVisualSVector;
typedef SpriteVisualSVector::Ref SpriteVisualRef;

//typedef StaticList<SpriteVisual> SpriteVisualSVector;
//typedef SpriteVisualSVector::Ref SpriteVisualRef;
