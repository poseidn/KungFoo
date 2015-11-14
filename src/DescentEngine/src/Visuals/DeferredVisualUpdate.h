#pragma once

#include <functional>

#include "VisualBase.h"

typedef std::function<void( VisualBase * )> DeferredVisualUpdate;

typedef std::pair<VisualBase *, DeferredVisualUpdate> VisualUpdatePair;
