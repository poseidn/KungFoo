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
