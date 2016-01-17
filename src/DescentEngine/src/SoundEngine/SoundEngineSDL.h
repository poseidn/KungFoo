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

