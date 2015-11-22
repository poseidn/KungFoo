#include "ResourceEngineAndroid.h"

#include "../Log.h"
#include "../Texture.h"

void ResourceEngineAndroid::preloadImage(std::string const& imageName, GLuint glId, size_t frameCount) {
	std::string imageNameExt = imageName + defaultImageExt();

	// create already bound texture
	auto texPtr = std14::make_unique<Texture>(glId, frameCount);
	m_textures[imageNameExt] = std::move(texPtr);
	logging::Info() << "image " << imageNameExt << " preloaded";
}

TexturePtr ResourceEngineAndroid::loadImage(std::string const& imageName, unsigned int frames) {
	std::string imageNameExt = imageName + defaultImageExt();

	return loadImageIntern(imageNameExt, frames, true);
}

TexturePtr ResourceEngineAndroid::loadImageIntern(std::string const& imageNameExt, unsigned int frames,
		bool useCache) {

	if (useCache) {
		auto res = checkTextureCache(imageNameExt);
		if (res.first) {
			return res.second;
		}
	}

	int id = m_javaInterface->loadImage(imageNameExt);

	// create texture which is already bound ( was done on the android side )
	auto tex = std14::make_unique<Texture>(id, frames);
	TexturePtr texPtr = tex.get();
	m_textures[imageNameExt] = std::move(tex);
	return texPtr;
}

void ResourceEngineAndroid::reloadAllTextures() {
	for (auto & tex : m_textures) {
		std::string texName = tex.first;

		// internal, because the image extension has already been added !
		auto texPtr = loadImageIntern(texName, tex.second->getAnimationFrames(), false);
		// we just need the id
		logging::Info() << "Prev id : " << tex.second->getID() << " newId: " << texPtr->getID();
		tex.second->setID(texPtr->getID());
		tex.second->setPixelPointer(texPtr->getPixelPointer());
	}
}

std::string ResourceEngineAndroid::loadLevel(std::string const& levelName) {
	//logging::Fatal() << " not implemented";
	if (!assertInterface())
		return "";

	const std::string fileName(getLevelPrefix() + levelName + ".xml");
	std::string result = m_javaInterface->readTextFile(fileName);

	return result;
}

std::string ResourceEngineAndroid::loadScript(std::string const& scriptName) {
	if (!assertInterface())
		return "";

	const std::string fileName(getScriptPrefix() + scriptName + ".lua");
	std::string result = m_javaInterface->readTextFile(fileName);

	logging::Info() << "lua script loaded : " << result;

	return result;
}
