/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

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
