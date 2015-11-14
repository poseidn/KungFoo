#include "ResourceEngine.h"

#include "../Texture.h"

void ResourceEngineAbstract::freeResources() {
	//for (TexturesMap::iterator it = m_textures.begin(); it != m_textures.end(); it++) {

	for (auto & tex : m_textures) {

		// overrides of 'freeTexture' in subclasses are not available in the destructor of 'ResourceEngineAbstract'
		// ... wow
		// but clear: the subclass has already been destroyed and therefore is invalid to be used
		this->freeTexture(tex.second.get());
	}
	m_textures.clear();

	for (auto & snd : m_sounds) {
		this->freeSound(snd.second);
		// don't delete sound pointer, it is either only a pointer ( SDL )
		// or a string ( Android )
	}
	m_sounds.clear();

	for (auto & snd : m_music) {
		this->freeMusic(snd.second);
		// don't delete music pointer, it is either only a pointer ( SDL )
		// or a string ( Android )
	}
	m_music.clear();
}

ResourceEngineAbstract::~ResourceEngineAbstract() {
}
