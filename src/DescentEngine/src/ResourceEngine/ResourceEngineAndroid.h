#pragma once

#include "ResourceEngine.h"

#include "../JavaInterface.h"

class ResourceEngineAndroid: public ResourceEngineAbstract {
public:

	ResourceEngineAndroid() :
			m_javaInterface(nullptr) {
	}

	// todo: don't load the same image twice, but return a ref to the actually loaded
	virtual TexturePtr loadImage(std::string const& imageName, unsigned int frames = 1) CPP11_OVERRIDE;

	virtual SoundPtr loadSound(std::string const& soundName) CPP11_OVERRIDE
	{
		return SoundPtr(soundName);
	}

	virtual MusicPtr loadMusic(std::string const& musicName) CPP11_OVERRIDE
	{
		return SoundPtr(musicName);
	}

	virtual std::string loadLevel(std::string const& levelName) CPP11_OVERRIDE;

	virtual std::string loadScript(std::string const& scriptName) CPP11_OVERRIDE;

	// just put an already loaded texture into the texture cache
	virtual void preloadImage(std::string const& imageName, GLuint glId, size_t frameCount = 1) CPP11_OVERRIDE;

	void setJavaInterface(JavaInterface * ji) {
		m_javaInterface = ji;
	}

	// this is necessary if the application has been paused
	void reloadAllTextures();

protected:
	void freeTexture(TexturePtr) CPP11_OVERRIDE {
	}

	void freeSound(SoundPtr) CPP11_OVERRIDE {
	}

	void freeMusic(MusicPtr) CPP11_OVERRIDE {
	}

private:

	TexturePtr loadImageIntern(std::string const& imageNameExt, unsigned int frames, bool useCache = true);

	bool assertInterface() const {
		if (m_javaInterface != nullptr) {
			if (m_javaInterface->isValid())
				return true;
		}
		logging::Fatal() << "ResourceEngineAndroid: Java Interface not set prorperly";
		return false;
	}

	JavaInterface * m_javaInterface;

};

class ResourceEngine CPP11_FINAL: public ResourceEngineAndroid {
public:
	virtual ~ResourceEngine() {
	}
};

