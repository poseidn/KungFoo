#include "InputContainer.h"

// because we compare to the magSquared of the stick vector...
CPP11_CONSTEXPR float InputContainer::StickOneDeadZone = 25.0f * 25.0f;
// needs to be in sync with the Android InpuContainer
CPP11_CONSTEXPR float InputContainer::StickOneMax = 100.0f;
