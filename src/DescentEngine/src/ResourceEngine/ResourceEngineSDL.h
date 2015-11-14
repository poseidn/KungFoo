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
	virtual TexturePtr loadImage(std::string const& imageName, unsigned int frames = 1) CPP11_OVERRIDE;

	virtual SoundPtr loadSound(std::string const& soundName) CPP11_OVERRIDE;
	virtual MusicPtr loadMusic(std::string const& musicName) CPP11_OVERRIDE;

	virtual std::string loadLevel(std::string const& levelName) CPP11_OVERRIDE;
	virtual std::string loadScript(std::string const& scriptName) CPP11_OVERRIDE;

	virtual std::string getScriptPath(std::string const & scriptName) CPP11_OVERRIDE;

	// just put an already loaded texture into the texture cache
	virtual void preloadImage(std::string const& imageName, GLuint glId, size_t frameCount = 1) CPP11_OVERRIDE;

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

