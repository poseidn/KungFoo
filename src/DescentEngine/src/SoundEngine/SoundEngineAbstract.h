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

#include <boost/noncopyable.hpp>
#include <vector>

#include "../Cpp11.h"

#include "../Log.h"

#include "SoundPtr.h"
#include "PlayHandle.h"

// todo: make this also work without a sound card !
class SoundEngineAbstract: boost::noncopyable {
public:
	SoundEngineAbstract() :
			m_mute(false) {
	}

	// direction 0.0f is from center, -1.0f is from the very left ...
	virtual PlayHandle playSound(SoundPtr snd, float direction = 0.0f) =0;

	virtual PlayHandle playMusic(MusicPtr msc) = 0;

	// fadeOut time in ms
	virtual void stopPlay(PlayHandle const& ph, float fadeOutTime = -1.0f) = 0;

	bool isMuted() const {
		return m_mute;
	}

	virtual void startVibratePattern(std::string const&) {
	}

	virtual void stopAllViberatePatterns() {
	}

	virtual void stopVibratePattern(std::string const&) {
	}

	void setMuted(bool m) {
		m_mute = m;
	}

	virtual void pauseSound() {
	}

	virtual void resumeSound() {
	}

	virtual ~SoundEngineAbstract() {
	}
private:
	bool m_mute;
};
