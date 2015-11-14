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
