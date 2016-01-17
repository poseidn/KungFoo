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

#include "ResourceEngine.h"
#include <android/asset_manager.h>

#include "../JavaInterface.h"

class ResourceEngineAndroid: public ResourceEngineAbstract {
public:

	ResourceEngineAndroid() :
			m_javaInterface(nullptr) {
	}

	// todo: don't load the same image twice, but return a ref to the actually loaded
	virtual TexturePtr loadImage(std::string const& imageName,
			unsigned int frames = 1) CPP11_OVERRIDE;

	virtual SoundPtr loadSound(std::string const& soundName) CPP11_OVERRIDE
	{
		return SoundPtr(soundName);
	}

	virtual MusicPtr loadMusic(std::string const& musicName) CPP11_OVERRIDE
	{
		return SoundPtr(musicName);
	}

	virtual std::string loadLevel(std::string const& levelName) CPP11_OVERRIDE;

	// just put an already loaded texture into the texture cache
	virtual void preloadImage(std::string const& imageName, GLuint glId,
			size_t frameCount = 1) CPP11_OVERRIDE;

	void setJavaInterface(JavaInterface * ji) {
		m_javaInterface = ji;
	}

	// this is necessary if the application has been paused
	// todo: remove
	void reloadAllTextures();

	// needs to be done before android destroys the OpenGL ES context
	// todo: implement
	void freeAllTextures();

	void setAssetManager(AAssetManager * as) {
		m_assetManager = as;
	}

protected:
	void freeTexture(TexturePtr) CPP11_OVERRIDE {
	}

	void freeSound(SoundPtr) CPP11_OVERRIDE {
	}

	void freeMusic(MusicPtr) CPP11_OVERRIDE {
	}

private:

	TexturePtr loadImageIntern(std::string const& imageNameExt,
			unsigned int frames, bool useCache = true);

	bool assertAssetManager() const {
		if (m_assetManager == nullptr) {
			logging::Fatal()
					<< "ResourceEngineAndroid: Java Interface not set properly";
			return false;
		}
		return true;
	}

	JavaInterface * m_javaInterface;
	AAssetManager * m_assetManager = nullptr;

};

class ResourceEngine CPP11_FINAL: public ResourceEngineAndroid {
public:
	virtual ~ResourceEngine() {
	}
};

