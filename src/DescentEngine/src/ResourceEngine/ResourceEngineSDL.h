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

class ResourceEngineSDL: public ResourceEngineAbstract {
public:

	// resources will be freed in the base class
	virtual ~ResourceEngineSDL() CPP11_OVERRIDE {
		logging::Info() << "ResourceEngineSDL dstor";
		//wil lnot be called
	}

	// todo: don't load the same image twice, but return a ref to the actually loaded
	TexturePtr loadImage(std::string const& imageName, unsigned int frames = 1)
			CPP11_OVERRIDE;

	SoundPtr loadSound(std::string const& soundName) CPP11_OVERRIDE;
	MusicPtr loadMusic(std::string const& musicName) CPP11_OVERRIDE;

	std::string loadLevel(std::string const& levelName) CPP11_OVERRIDE;

	std::string getScriptPath(std::string const & scriptName) CPP11_OVERRIDE;

	// just put an already loaded texture into the texture cache
	void preloadImage(std::string const& imageName, GLuint glId,
			size_t frameCount = 1) CPP11_OVERRIDE;

protected:
	void freeTexture(TexturePtr) CPP11_OVERRIDE;
	void freeSound(SoundPtr) CPP11_OVERRIDE;
	void freeMusic(MusicPtr) CPP11_OVERRIDE;

	std::string loadTextFile(std::string const& fileName);

};

class ResourceEngine CPP11_FINAL: public ResourceEngineSDL {
public:
	virtual ~ResourceEngine() {
	}
};

