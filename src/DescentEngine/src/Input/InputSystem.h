#pragma once

#include "../Cpp11.h"

#include "MultiplexedInput.h"
#include "DelayedInput.h"

#ifdef USE_SDL

#include "SDLInput.h"

// todo: refactor this SLDInput to be fixed here
class InputSystem CPP11_FINAL : public MultiplexedInput<SDLInput, DelayedInput>
{
public:
	InputSystem ( SDLInput * iA, DelayedInput * iB ): MultiplexedInput ( iA, iB) {}

};

#endif

#ifdef USE_ANDROID

#include "AndroidInput.h"

class InputSystem CPP11_FINAL : public AndroidInput {

};
#endif
