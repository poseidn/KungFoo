#pragma once

#include "../Cpp11.h"

#include "SoundEngineAbstract.h"

class SoundEngineSDL: public SoundEngineAbstract {
public:
	// todo: move to an intialize call
	SoundEngineSDL();
	virtual ~SoundEngineSDL();

	virtual PlayHandle playSound(SoundPtr snd, float direction = 0.0f) CPP11_OVERRIDE;

	virtual PlayHandle playMusic(MusicPtr msc) CPP11_OVERRIDE;

	virtual void stopPlay(PlayHandle const& ph, float fadeOutTime = -1.0f) CPP11_OVERRIDE;

private:
	PlayHandle m_fixedMusicHandle;
};

class SoundEngine CPP11_FINAL : public SoundEngineSDL {
public:
	virtual ~SoundEngine() {
	}
};

