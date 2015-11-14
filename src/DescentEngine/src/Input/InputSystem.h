#pragma once

#include "../Cpp11.h"

#include "MultiplexedInput.h"
#include "DelayedInput.h"

#ifdef USE_SDL

#include "SDLInput.h"

class InputSystem CPP11_FINAL : public MultiplexedInput<SDLInput, DelayedInput>
{
public:
	InputSystem ( SDLInput * iA, DelayedInput * iB ): MultiplexedInput ( iA, iB) {}

};

#endif

#ifdef USE_ANDROID

#include "AndroidInput.h"

class InputSystem CPP11_FINAL : public MultiplexedInput<AndroidInput, DelayedInput>
{
public:
	InputSystem ( AndroidInput * iA, DelayedInput * iB ): MultiplexedInput ( iA, iB), m_androidInput ( iA ) {}

	void injectDirectionStickOne( InputSystemBase::ContainerId id, Vector2 newMovement)
	{
		InputContainer & cont = getContainerByContainerId( id );

		m_androidInput->injectDirectionStickOne ( cont, newMovement );
	}

	void injectKeyDown(InputSystemBase::ContainerId id, int keyId)
	{
		InputContainer & cont = getContainerByContainerId( id );

		m_androidInput->injectKeyDown( cont, id, keyId );
	}

	void registerInputDevice( InputSystemBase::ContainerId id )
	{
		m_androidInput->registerInputDevice( id );
	}

private:
	AndroidInput * m_androidInput;
};

#endif
