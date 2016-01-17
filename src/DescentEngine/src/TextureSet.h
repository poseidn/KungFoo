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
