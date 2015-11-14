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
