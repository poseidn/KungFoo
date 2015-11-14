#pragma once

//#include <boost/tr_container/ptr_vector.hpp>
#include <list>
#include <vector>

class LightVisual;

typedef std::list<LightVisual *> LightVisualList;

typedef std::vector<LightVisual *> LightVisualVectorAdd;
typedef std::vector<LightVisual *> LightVisualVector;

