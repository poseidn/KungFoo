#pragma once

#ifdef USE_SDL

#include "../SDL_include.h"

typedef Mix_Chunk * SoundPtr;
typedef Mix_Music * MusicPtr;

#endif

#ifdef USE_ANDROID

// on Android, this is simply a proxy for the sound name,
// as all sounds will be played by the Java side

typedef std::string SoundPtr;
typedef std::string MusicPtr;

#endif

/*
 typedef Mix_Chunk * SoundPtr;

 class SoundPtr {
 public:
 SoundPtr() {

 }

 Mix_Music

 private:
 Mix_Music * m_musicPtr;
 };

 */
