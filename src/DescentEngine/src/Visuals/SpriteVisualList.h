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
