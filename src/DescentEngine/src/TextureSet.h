#pragma once

#include <boost/noncopyable.hpp>
#include <vector>
#include "TextureRef.h"

typedef unsigned int TextureId;

class TextureSetEntry/*: boost::noncopyable*/{
public:
	TextureSetEntry(TexturePtr ptr, TextureId id = 0, float timing = 0.0f) :
			m_ptr(ptr), m_id(id), m_frameTiming(timing) {

	}

	TextureId getId() const {
		return m_id;
	}

	TexturePtr getTexturePtr() const {
		return m_ptr;
	}

	float getFrameTiming() const {
		return m_frameTiming;
	}

private:
	TexturePtr m_ptr;
	TextureId m_id;
	float m_frameTiming;
};

typedef std::vector<TextureSetEntry> TextureSet;
