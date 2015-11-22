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

