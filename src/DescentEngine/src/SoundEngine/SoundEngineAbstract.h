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

	void setMuted(bool m) {
		m_mute = m;
	}

	virtual ~SoundEngineAbstract() {
	}
private:
	bool m_mute;
};
