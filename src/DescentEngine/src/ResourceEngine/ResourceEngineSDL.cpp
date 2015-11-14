#include "ResourceEngine.h"

#include <fstream>
#include <sstream>
//#include <unistd.h>

#include "Texture.h"

#include "../SDL_include.h"

void ResourceEngineSDL::preloadImage(std::string const& imageName, GLuint glId, size_t frameCount) {
	logging::Fatal() << "preloading of images not supported by SDL";
}

std::string ResourceEngineSDL::getScriptPath(std::string const & scriptName) {
	return getScriptPrefix() + scriptName + ".lua";
}

std::string ResourceEngineSDL::loadScript(std::string const& scriptName) {
	return loadTextFile(getScriptPath(scriptName));
}

std::string ResourceEngineSDL::loadTextFile(std::string const& fileName) {
	std::ifstream fileIn(fileName);

	std::string buffer;
	std::stringstream bufferAll;
	const size_t maxBuffer = 1024;
	char inBuffer[maxBuffer];

	if (fileIn.is_open()) {

		while (fileIn.good()) {
			std::string line;
			std::getline(fileIn, line);
			bufferAll << line << std::endl;
		}
		fileIn.close();
	} else {
		logging::Fatal() << "Cannot open file " << fileName;
	}

	return bufferAll.str();
}

std::string ResourceEngineSDL::loadLevel(std::string const& levelName) {
	const std::string fileName(getLevelPrefix() + levelName + ".xml");
	return loadTextFile(fileName);
}

MusicPtr ResourceEngineSDL::loadMusic(std::string const& musicName) {

	// todo: also make generic
	if (m_music.find(musicName) != m_music.end()) {
		// already loaded this texture
		//logging::Info() << "Returning cached sound " << musicName;
		return MusicPtr(m_music.at(musicName));
	}

	Mix_Music *sample;
	std::string fullPath = getSoundPrefix() + musicName + defaultSoundExt();
	sample = Mix_LoadMUS(fullPath.c_str());
	if (!sample) {
		logging::Fatal() << "cannot load sound " << musicName << " from pull path " << fullPath;
		// handle error
	}
	m_music[musicName] = MusicPtr(sample);
	return sample;
}

SoundPtr ResourceEngineSDL::loadSound(std::string const& soundName) {

	if (m_sounds.find(soundName) != m_sounds.end()) {
		// already loaded this texture
		//logging::Info() << "Returning cached sound " << soundName;
		return SoundPtr(m_sounds.at(soundName));
	}

	Mix_Chunk *sample;
	std::string fullPath = getSoundPrefix() + soundName + defaultSoundExt();
	sample = Mix_LoadWAV(fullPath.c_str());
	if (!sample) {
		logging::Fatal() << "cannot load sound sound " << soundName << " from full path " << fullPath;
		// handle error
	}
	m_sounds[soundName] = SoundPtr(sample);
	return sample;
}

TexturePtr ResourceEngineSDL::loadImage(std::string const& imageName, unsigned int frames) {

	std::string imageNameExt = imageName + defaultImageExt();

	auto res = checkTextureCache(imageNameExt);
	if (res.first) {
		return res.second;
	}

	//usleep(10000);
	// new texture, load from storage
	logging::Info() << "Loading texture " << imageNameExt;

	// todo: this surface is leaked somehow, we need to free it when the
	// texture is killed ...
	const std::string fullPath(getImagePrefix() + imageNameExt);
	SDL_Surface * surface = IMG_Load(fullPath.c_str());

	if (surface != nullptr) {

		// Check that the image's width is a power of 2
		if ((surface->w & (surface->w - 1)) != 0) {
			logging::Fatal() << " image width is not a power of 2";
		}

		// Also check if the height is a power of 2
		if ((surface->h & (surface->h - 1)) != 0) {
			logging::Fatal() << " image height is not a power of 2";
		}
// get the number of channels in the SDL surface
		GLint nOfColors = surface->format->BytesPerPixel;
		GLenum texture_format;
		if (nOfColors == 4)	// contains an alpha channel
				{
			//logging::Info() << "Loaded texture has alpha channel";
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
				{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR;
		} else {
			logging::Fatal() << " the image is not truecolor..  this will probably break";
			// todo: exception
			return TexturePtr();
			// this error should not go unhandled
		}

		auto texPtr = std14::make_unique<Texture>(surface->h, surface->w, nOfColors, texture_format, surface->pixels,
				frames);
#ifdef USE_SDL
		texPtr->m_sdlSurface = surface;
#endif

#ifdef DESCENT_TEXTURE_NAME_DEBUG
		texPtr->setTextureName(imageNameExt);
#endif

		auto texRef = texPtr.get();
		m_textures[imageNameExt] = std::move(texPtr);

		return texRef;
	} else {
		logging::Fatal() << "Can't load texture from file " << imageNameExt << " from path " << fullPath;

		return TexturePtr(nullptr);
	}

}

void ResourceEngineSDL::freeTexture(TexturePtr tex) {
	SDL_FreeSurface(tex->m_sdlSurface);
}

void ResourceEngineSDL::freeSound(SoundPtr snd) {
	Mix_FreeChunk(snd);
}

void ResourceEngineSDL::freeMusic(MusicPtr snd) {
	Mix_FreeMusic(snd);
}

