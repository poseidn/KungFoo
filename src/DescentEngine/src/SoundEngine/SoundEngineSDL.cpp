#include "SoundEngineSDL.h"

#include "../SDL_include.h"

SoundEngineSDL::SoundEngineSDL() :
		SoundEngineAbstract(), m_fixedMusicHandle(-10) {
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
	auto actualNumber = Mix_AllocateChannels(255);
	logging::Info() << "Allocated " << actualNumber << " for sound mixing";

}

PlayHandle SoundEngineSDL::playSound(SoundPtr snd, float direction) {
	if (isMuted())
		return PlayHandle(0);
	// returns the channel which the sound is played on, we will pass this on to the game
	// todo: play the sound according to the direction given
	return PlayHandle(Mix_PlayChannel(-1, snd, 0));
}

PlayHandle SoundEngineSDL::playMusic(MusicPtr msc) {
	if (isMuted())
		return PlayHandle(0);
	Mix_PlayMusic(msc, -1);

	// there can only be one music piece at a time
	return m_fixedMusicHandle;
}

void SoundEngineSDL::stopPlay(PlayHandle const& ph, float fadeOutTime) {
	if (ph == m_fixedMusicHandle) {
		Mix_HaltMusic();
	} else {
		// todo: can be a problem if another sound is already running on this channel
		if (fadeOutTime > 0.0f) {
			Mix_FadeOutChannel(ph, fadeOutTime);
		} else {
			Mix_HaltChannel(ph);
		}
	}
}

SoundEngineSDL::~SoundEngineSDL() {
	Mix_CloseAudio();
	Mix_Quit();
}

