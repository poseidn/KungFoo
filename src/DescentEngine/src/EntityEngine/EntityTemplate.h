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

#include <string>

#include <boost/noncopyable.hpp>

#include "../TextureSet.h"
#include "../Rectangle.h"
#include "../Visuals/LayerPriority.h"

class RandomEngine;

enum class CollisionMode {
	AlwaysCollide, JumpNoCollide, NeverCollide
};

class EntityTemplate {
public:

	struct TextureConfig {
		TextureConfig(TextureId _id, std::vector<std::string> _fileName, size_t _frames, float _frameTiming =
				0.0f);
		std::string const& getRandomizedFileName(RandomEngine & randEg) const;

		TextureId Id;
		std::vector<std::string> FileName;
		size_t Frames;
		float FrameTiming;

	};

	EntityTemplate() = default;

	EntityTemplate(std::vector<TextureConfig> const& texConf, Rectangle2 const& _boundingBox,
			Rectangle2 const& _visualSize, LayerPriority _layerPrio, CollisionMode _colMode,
			bool _isTransparent, float _transp = 1.0f);

	typedef std::vector<TextureConfig> TextureNames;

	TextureNames Textures;
	Rectangle2 BoundingBox;
	Rectangle2 VisualSize;

	LayerPriority VisualPriority;

	CollisionMode Collision;
	// all the transparent stuff must be put at the end of the render queue in
	// order to make the blending work correctly
	bool IsTransparent;
	float Transparency;
};
