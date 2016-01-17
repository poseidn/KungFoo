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

#include "ResourceEngineAndroid.h"

#include "../Log.h"
#include "../Texture.h"

void ResourceEngineAndroid::preloadImage(std::string const& imageName,
		GLuint glId, size_t frameCount) {
	std::string imageNameExt = imageName + defaultImageExt();

	// create already bound texture
	auto texPtr = std14::make_unique<Texture>(glId, frameCount);
	m_textures[imageNameExt] = std::move(texPtr);
	logging::Info() << "image " << imageNameExt << " preloaded";
}

TexturePtr ResourceEngineAndroid::loadImage(std::string const& imageName,
		unsigned int frames) {
	std::string imageNameExt = imageName + defaultImageExt();

	return loadImageIntern(imageNameExt, frames, true);
}

TexturePtr ResourceEngineAndroid::loadImageIntern(
		std::string const& imageNameExt, unsigned int frames, bool useCache) {

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

void ResourceEngineAndroid::freeAllTextures() {
	for (auto & tex : m_textures) {
		m_javaInterface->freeTexture(tex.second->getID());
	}
	m_textures.clear();
	logging::Info() << "All textures freed";
}

void ResourceEngineAndroid::reloadAllTextures() {
	for (auto & tex : m_textures) {
		std::string texName = tex.first;

		// internal, because the image extension has already been added !
		auto texPtr = loadImageIntern(texName, tex.second->getAnimationFrames(),
				false);
		// we just need the id
		logging::Info() << "Prev id : " << tex.second->getID() << " newId: "
				<< texPtr->getID();
		tex.second->setID(texPtr->getID());
		tex.second->setPixelPointer(texPtr->getPixelPointer());
	}
}

std::string ResourceEngineAndroid::loadLevel(std::string const& levelName) {
	//logging::Fatal() << " not implemented";
	if (!assertAssetManager())
		return "";

	const std::string fileName(getLevelPrefix() + levelName + ".xml");
	AAsset * asset = AAssetManager_open(m_assetManager, fileName.c_str(),
			AASSET_MODE_STREAMING);

	if (asset == nullptr) {
		logging::Fatal() << "Asset with name " << fileName
				<< " could not be loaded.";
		return "";
	}

	constexpr size_t buffer_size = 1024;
	int bytes_read;
	char buffer[buffer_size];
	std::string textFileString;

	while (true) {
		bytes_read = AAsset_read(asset, &buffer, buffer_size);
		if (bytes_read < 0) {
			logging::Fatal() << "Error while reading from file " << fileName;
			return "";
		} else {
			std::string bufString(buffer);
			bufString.resize(bytes_read);
			textFileString.append(bufString);

			// at the end !
			if (bytes_read < buffer_size)
				break;
		}
	}

	logging::Info() << "Completed reading of file " << fileName;

	return textFileString;
}

