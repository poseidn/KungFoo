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

#include <utility>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <unordered_map>

#include "../Util.h"
#include "../Cpp11.h"
#include "../Log.h"
#include "../OpenGLInclude.h"

#include "../Texture.h"
#include "../TextureRef.h"
#include "../SoundEngine/SoundPtr.h"

class ResourceManager {
public:
	virtual void freeResources()= 0;
};

class ResourceEngineAbstract: public ResourceManager, private boost::noncopyable {
public:

	std::string defaultSoundExt() const {
		return ".ogg";
	}

	std::string defaultImageExt() const {
		return ".png";
	}

	std::string getImagePrefix() const {
		return "images/";
	}

	std::string getSoundPrefix() const {
		return "sounds/";
	}

	std::string getLevelPrefix() const {
		return "levels/";
	}

	std::string getScriptPrefix() const {
		return "scripts/";
	}

	virtual ~ResourceEngineAbstract();

	void freeResources() CPP11_OVERRIDE;

	// todo: don't load the same image twice, but return a ref to the actually loaded
	virtual TexturePtr loadImage(std::string const& imageName, unsigned int frames = 1) = 0;

	virtual SoundPtr loadSound(std::string const& soundName) = 0;
	virtual MusicPtr loadMusic(std::string const& musicName) = 0;

	virtual std::string loadLevel(std::string const& levelName) = 0;

	virtual std::string getScriptPath(std::string const & scriptName) {
		logging::NotImplemented();
		return "";
	}

	// just put an already loaded texture into the texture cache
	virtual void preloadImage(std::string const& imageName, GLuint glId, size_t frameCount = 1) = 0;

protected:

	// called by the constructor of this class to give child classes a chance
	// to free the image, for example delete it from the grafix ram
	virtual void freeTexture(TexturePtr tex) = 0;

	virtual void freeSound(SoundPtr snd) = 0;

	virtual void freeMusic(MusicPtr msc) = 0;

	std::pair<bool, Texture *> checkTextureCache(std::string const& imageName) const {
		if (m_textures.find(imageName) != m_textures.end()) {
			// already loaded this texture
			//logging::Info() << "Returning cached texture " << imageName;
			return std::make_pair(true, m_textures.at(imageName).get());
		} else {
			return std::make_pair(false, nullptr);
		}
	}

	typedef std::unordered_map<std::string, uniq<Texture>> TexturesMap;
	TexturesMap m_textures;

	// using no uniq here, because SoundPtr is a placeholder for either a pointer
	// coming from the android graphics system or a std::string in the case of SDL
	typedef std::unordered_map<std::string, SoundPtr> SoundMap;
	SoundMap m_sounds;

	// using no uniq here, because MusicMap is a placeholder for either a pointer
	// coming from the android sound system or a std::string in the case of SDL
	typedef std::unordered_map<std::string, MusicPtr> MusicMap;
	MusicMap m_music;
};

#ifdef USE_SDL

#include "ResourceEngineSDL.h"

#endif

#ifdef USE_ANDROID

#include "ResourceEngineAndroid.h"

#endif

