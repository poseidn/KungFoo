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
