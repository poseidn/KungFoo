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
	void stopPlay(PlayHandle const& ph, float fadeOutTime = -1.0f) CPP11_OVERRIDE {
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

