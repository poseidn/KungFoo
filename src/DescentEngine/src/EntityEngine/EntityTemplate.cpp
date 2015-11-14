#include "EntityTemplate.h"

#include <cassert>
#include "../RandomEngine.h"

std::string const& EntityTemplate::TextureConfig::getRandomizedFileName(RandomEngine & randEg) const {
	assert(FileName.size() > 0);
	if (FileName.size() == 1)
		return FileName[0];

	//auto timeNow = std::chrono::high_resolution_clock::now();
	unsigned int fileIndex = 0;
	fileIndex = randEg.randomInt(RandomEngine::SpanInt(0, FileName.size() - 1));

	return FileName[fileIndex];
}

EntityTemplate::TextureConfig::TextureConfig(TextureId _id, std::vector<std::string> _fileName, size_t _frames,
		float _frameTiming) :
		Id(_id), FileName(_fileName), Frames(_frames), FrameTiming(_frameTiming) {
}

EntityTemplate::EntityTemplate(std::vector<TextureConfig> const& texConf, Rectangle2 const& _boundingBox,
		Rectangle2 const& _visualSize, LayerPriority _layerPrio, CollisionMode _colMode, bool _isTransparent,
		float _transp) :
		Textures(texConf), BoundingBox(_boundingBox), VisualSize(_visualSize), VisualPriority(_layerPrio), Collision(
				_colMode), IsTransparent(_isTransparent), Transparency(_transp) {
}
