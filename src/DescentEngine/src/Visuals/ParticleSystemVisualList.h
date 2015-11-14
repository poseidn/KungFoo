#pragma once

#include "ParticleSystemVisual.h"
#include "../Util.h"

#include <list>
#include <vector>


typedef std::list<ParticleSystemVisual *> ParticeSystemVisualList;
typedef std::list<uniq<ParticleSystemVisual>> ParticeSystemVisualListUniq;

typedef std::vector<ParticleSystemVisual *> ParticeSystemVisualVectorAdd;
typedef std::vector<ParticleSystemVisual *> ParticeSystemVisualVector;

