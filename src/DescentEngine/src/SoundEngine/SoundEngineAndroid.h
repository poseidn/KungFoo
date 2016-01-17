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
#include "../JavaInterface.h"

class SoundEngineAndroid: public SoundEngineAbstract {
public:
	typedef std::vector<SoundPtr> SoundsToPlay;
	typedef std::vector<MusicPtr> MusicToPlay;

	SoundEngineAndroid() :
			SoundEngineAbstract(), m_javaInterface(nullptr) {
		logging::Info() << "Android Sound Engine initialized ";

	}

	PlayHandle playSound(SoundPtr snd, float direction = 0.0f) CPP11_OVERRIDE {
		if (isMuted())
			return PlayHandle(0);

		auto hndl = m_javaInterface->playSound(snd, direction);
		return PlayHandle(hndl);
	}

	PlayHandle playMusic(MusicPtr msc) CPP11_OVERRIDE {
		if (isMuted())
			return PlayHandle(0);

		auto hndl = m_javaInterface->playMusic(msc);
		return PlayHandle(hndl);
	}

	// fadeOut time in ms
	void stopPlay(PlayHandle const& ph, float fadeOutTime = -1.0f)
			CPP11_OVERRIDE {
		m_javaInterface->stopPlay(ph, fadeOutTime);
	}

	void resumeSound() CPP11_OVERRIDE {
		m_javaInterface->resumeSound();
	}

	void pauseSound() CPP11_OVERRIDE {
		m_javaInterface->pauseSound();
	}

	virtual ~SoundEngineAndroid() {
	}

	void startVibratePattern(std::string const& patternName) CPP11_OVERRIDE {
		m_javaInterface->startVibratePattern(patternName);
	}

	void stopAllViberatePatterns() CPP11_OVERRIDE {
		m_javaInterface->stopAllViberatePatterns();
	}

	void stopVibratePattern(std::string const& patternName) CPP11_OVERRIDE {
		m_javaInterface->stopVibratePattern(patternName);
	}

	void setJavaInterface(JavaInterface * ji) {
		m_javaInterface = ji;
	}

private:

	JavaInterface * m_javaInterface;
};

class SoundEngine CPP11_FINAL: public SoundEngineAndroid {
public:
	virtual ~SoundEngine() {
	}
};

