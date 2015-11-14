#pragma once

#include "../ResourceEngine/ResourceEngine.h"
#include "../AnimationEngine/AnimationEngine.h"

#include "../Engines.h"
#include "TextVisual.h"
#include "../AnimationEngine/TextAnimation.h"

namespace TextSupport {

inline void ingameTextFadeOut(Engines & engines, Vector2 const& initialPos, std::string const& text,
		float offsetTime = 0.25f) {
	TexturePtr textTex = engines.resourceEngine().loadImage("textChars");

	auto vis = std14::make_unique<TextVisual>(engines.renderEngine().getScreenTransform(), textTex, initialPos, text);
	vis->setIngame(true);
	// todo: clean up the visual once it gets out of the screen !

	// enable fading animation ...
	// will be auto-remove as soon as the animation is complete
	auto anim = TextAnimation(vis.get(), offsetTime, 0.5f, true);

	engines.renderEngine().addTextVisual(std::move(vis));
	engines.animationEngine().addTextAnimation(anim);

}

}
