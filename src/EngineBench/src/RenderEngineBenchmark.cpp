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

#include "RenderEngineBenckmark.h"
#include "FakeGL.h"

void Bench_Render::renderSpriteVisual(SpriteVisualSVector & visualVec, bool ingameSprite, float deltaT) {

	TexturePtr lastBindTexture = nullptr;

	// std list	version: 40 % cache misses
	/*for (auto it = visualVec.begin(); it != visualVec.end(); it++) {
		SpriteVisual * vis = *it;
		if (vis->getVisible() && (vis->isIngame() == ingameSprite)) {
			vis->step(deltaT);

			FakeGL::glColor4f(1.0f, 1.0f, 1.0f, vis->getTransparency());

			FakeGL::glVertexPointer(3, GL_FLOAT, 0, vis->getVertexBufferPtr());
			FakeGL::glNormalPointer(GL_FLOAT, 0, vis->getNormalBufferPtr());
			FakeGL::glTexCoordPointer(2, GL_FLOAT, 0, vis->getDefaultTextureCoordsPtr());

			FakeGL::glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		}
	}*/

	// std :: vector : 4% cache misses
	/*for (size_t i = 0; i < visualVec.activeSize(); i++) {
	 if (!visualVec.isActive(i))
	 continue;

	 auto & vis = visualVec.get(i);
	 if (vis.getVisible() && (vis.isIngame() == ingameSprite)) {
	 vis.step(deltaT);

	 FakeGL::glColor4f(1.0f, 1.0f, 1.0f, vis.getTransparency());

	 FakeGL::glVertexPointer(3, GL_FLOAT, 0, vis.getVertexBufferPtr());
	 FakeGL::glNormalPointer(GL_FLOAT, 0, vis.getNormalBufferPtr());
	 FakeGL::glTexCoordPointer(2, GL_FLOAT, 0, vis.getDefaultTextureCoordsPtr());

	 FakeGL::glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	 }
	 }*/
}

template<>
RenderEngineAbstract<BenchOpenGLInterface, Bench_Render, BenchState>::RenderEngineAbstract() {

}

template<>
RenderEngineAbstract<BenchOpenGLInterface, Bench_Render, BenchState>::~RenderEngineAbstract() {
	clearSpriteList();
}
