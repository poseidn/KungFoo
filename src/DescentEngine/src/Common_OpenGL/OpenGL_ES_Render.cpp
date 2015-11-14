#include "OpenGL_ES_Render.h"
#include "../Log.h"
#include "../Visuals/SpriteVisual.h"
#include "../Visuals/LightVisual.h"
#include "../Visuals/ParticleSystemVisual.h"
#include "../Visuals/TextVisual.h"
#include "../Performance/SectionTimer.h"
#include "../Performance/BranchPredict.h"

void OpenGL_ES_Render::renderTextVisual(TextVisualListUniq const& part, bool ingameText) {
	//return;
	// todo: unbind texture after done so the debug visual drawing can work again
	GL_CHECK_ERROR(glMatrixMode(GL_MODELVIEW));
	GL_CHECK_ERROR(glLoadIdentity());

	//GL_CHECK_ERROR(glDisable(GL_LIGHTING));
	GL_CHECK_ERROR(glEnable(GL_TEXTURE_2D));

	GL_CHECK_ERROR(glDisableClientState(GL_NORMAL_ARRAY));
	GL_CHECK_ERROR(glEnableClientState(GL_VERTEX_ARRAY));
	GL_CHECK_ERROR(glEnableClientState(GL_TEXTURE_COORD_ARRAY));

	TexturePtr lastBindTexture = nullptr;

	for (auto & tv : part) {
		logging::DebugC<logging::Categories::RenderEngine>() << "ensureOpenGLBind";
		tv->getTexture()->ensureOpenGLBind();

		if (tv->isIngame() != ingameText)
			continue;

		if (tv->getVisible()) {
			glColor4f(1.0f, 1.0f, 1.0f, tv->getTransparency());

			// todo:: do this only once and then draw all entities with
			// this text -> sort the entities
			//if ( GCC_UNLIKELY (lastBindTexture != tv->getTexture() ) ) {
			if (lastBindTexture != tv->getTexture()) {
				//logging::DebugC<logging::Categories::RenderEngine>() << "Binding Texture with OpenGL";
				GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, tv->getTexture()->getID()));
				lastBindTexture = tv->getTexture();
			}

			logging::DebugC<logging::Categories::RenderEngine>() << "Setting up vertex Pointer";
			GL_CHECK_ERROR(glVertexPointer(3, GL_FLOAT, 0, &tv->getVertexBuffer().front()));
			//GL_CHECK_ERROR(glNormalPointer(GL_FLOAT, 0, (*it)->getNormalBufferPtr()));

			logging::DebugC<logging::Categories::RenderEngine>() << "Setting up tex coords";
			GL_CHECK_ERROR(glTexCoordPointer(2, GL_FLOAT, 0, &tv->getTextureBuffer().front()));

			logging::DebugC<logging::Categories::RenderEngine>() << "Draw arr";
			//logging::Debug<>() << "draw " << i;

			// this produces the scanline crash
			GL_CHECK_ERROR(glDrawArrays(GL_TRIANGLES, 0, 6 * tv->getCharacterCount()));
		}
	}

	GL_CHECK_ERROR(glDisableClientState(GL_VERTEX_ARRAY));
	GL_CHECK_ERROR(glDisableClientState(GL_TEXTURE_COORD_ARRAY));

}

void OpenGL_ES_Render::renderParticleSystemVisual(ParticeSystemVisualListUniq const& part) {

	GL_CHECK_ERROR(glMatrixMode(GL_MODELVIEW));
	GL_CHECK_ERROR(glLoadIdentity());

	GL_CHECK_ERROR(glDisable(GL_TEXTURE_2D));

	GL_CHECK_ERROR(glDisableClientState(GL_NORMAL_ARRAY));
	GL_CHECK_ERROR(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
	GL_CHECK_ERROR(glEnableClientState(GL_VERTEX_ARRAY));
	GL_CHECK_ERROR(glEnableClientState(GL_COLOR_ARRAY));

	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	for (auto & visual : part) {
		if (visual->getVisible() && visual->isRunning()) {
			GL_CHECK_ERROR(glPointSize(visual->getPointSize()));

			GL_CHECK_ERROR(glVertexPointer(3, GL_FLOAT, 0, visual->getVertexBufferPtr()));
			GL_CHECK_ERROR(glColorPointer(4, GL_FLOAT, 0, visual->getColorBufferPtr()));

			// this produces the scanline crash
			GL_CHECK_ERROR(glDrawArrays(GL_POINTS, 0, visual->getParticleCount()));
		}
	}
	GL_CHECK_ERROR(glDisableClientState(GL_VERTEX_ARRAY));
	GL_CHECK_ERROR(glDisableClientState(GL_COLOR_ARRAY));

}

void OpenGL_ES_Render::renderSpriteVisual(SpriteVisualSVector & visualVec, bool ingameSprite, float deltaT) {

	GL_CHECK_ERROR(glMatrixMode(GL_MODELVIEW));
	GL_CHECK_ERROR(glLoadIdentity());
	GL_CHECK_ERROR(glEnable(GL_TEXTURE_2D));

	GL_CHECK_ERROR(glEnableClientState(GL_VERTEX_ARRAY));
	GL_CHECK_ERROR(glEnableClientState(GL_NORMAL_ARRAY));
	GL_CHECK_ERROR(glEnableClientState(GL_TEXTURE_COORD_ARRAY));

	TexturePtr lastBindTexture = nullptr;

	for (size_t i = 0; i < visualVec.activeSize(); i++) {

		if (!visualVec.isActive(i))
			continue;

		auto & vis = visualVec.get(i);

		if (vis.getVisible() && (vis.isIngame() == ingameSprite)) {
			vis.step(deltaT);

			glColor4f(1.0f, 1.0f, 1.0f, vis.getTransparency());

			logging::DebugC<logging::Categories::RenderEngine>() << "ensureOpenGLBind";
			vis.getTexture()->ensureOpenGLBind();

			// render entries are presorted by texture
			// this case should not happen to often
			if (GCC_UNLIKELY(lastBindTexture != vis.getTexture())) {
				GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, vis.getTexture()->getID()));
				lastBindTexture = vis.getTexture();
			}

			logging::DebugC<logging::Categories::RenderEngine>() << "Setting up vertex Pointer";
			GL_CHECK_ERROR(glVertexPointer(3, GL_FLOAT, 0, vis.getVertexBufferPtr()));
			GL_CHECK_ERROR(glNormalPointer(GL_FLOAT, 0, vis.getNormalBufferPtr()));

			logging::DebugC<logging::Categories::RenderEngine>() << "Setting up tex coords";
			GL_CHECK_ERROR(glTexCoordPointer(2, GL_FLOAT, 0, vis.getDefaultTextureCoordsPtr()));

			logging::DebugC<logging::Categories::RenderEngine>() << "Draw arr";

			GL_CHECK_ERROR(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
		}
	} // visuals

	GL_CHECK_ERROR(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
	GL_CHECK_ERROR(glDisable(GL_TEXTURE_2D));

// run the loop again with debug faces, if needed
	if (m_debugFaces) {

		std::array<GLfloat, 4 * 4> debugFacesColor = { { //
				0.2f, 0.2f, 1.0f, 0.3f, //
						0.2f, 0.2f, 1.0f, 0.3f, //
						0.2f, 0.2f, 1.0f, 0.3f, //
						0.2f, 0.2f, 1.0f, 0.3f } };

		GL_CHECK_ERROR(glEnableClientState(GL_COLOR_ARRAY));
		const float zLayerDebug = LayerTools::computeZ(LayerPriority::LayerPriorityDebug);

		for (size_t i = 0; i < visualVec.activeSize(); i++) {
			if (!visualVec.isActive(i))
				continue;

			auto & vis = visualVec.get(i);

			if (vis.getVisible() && (vis.isIngame() == ingameSprite)) {
				// move the debug plane slightly above the actual texture planes
				SpriteVisual::VertexBufferArray vrtArr;
				auto const& otherArr = vis.getVertexBuffer();
				std::copy(otherArr, otherArr + SpriteVisual::VertexBufferSize, vrtArr);
				vrtArr[2] = vrtArr[5] = vrtArr[8] = vrtArr[11] = zLayerDebug;

				GL_CHECK_ERROR(glVertexPointer(3, GL_FLOAT, 0, &vrtArr ));
				GL_CHECK_ERROR(glNormalPointer(GL_FLOAT, 0, vis.getNormalBufferPtr()));
				GL_CHECK_ERROR(glColorPointer(4, GL_FLOAT, 0, &debugFacesColor.front() ));
				GL_CHECK_ERROR(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
			}
		}

		GL_CHECK_ERROR(glDisableClientState(GL_COLOR_ARRAY));
	}

	GL_CHECK_ERROR(glDisableClientState(GL_NORMAL_ARRAY));
	GL_CHECK_ERROR(glDisableClientState(GL_VERTEX_ARRAY));

}

void OpenGL_ES_Render::renderBegin() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	renderSetupCam();
}

void OpenGL_ES_Render::renderSetupCam() {

	GL_CHECK_ERROR(glMatrixMode(GL_PROJECTION));
	GL_CHECK_ERROR(glLoadIdentity());

	GL_CHECK_ERROR(glMultMatrixf(&m_defaultProjection.front()));
	GL_CHECK_ERROR(glTranslatef(0.0f, m_camTranslate.y(), 0.0f));
}

void OpenGL_ES_Render::setCameraLocation(ScreenTransform const& st, Vector3 const& vec, bool useOffsetX,
		bool useOffsetY) {
	m_defaultProjection = GLSupport::getParallelProjection(st.getScreenSize().x(), st.getScreenSize().y(),
			-1.0f, 1.0f);

	const Vector2 screenEdges = st.screenSizeInPixel();

	m_camTranslate = st.vectorToScreen(vec, useOffsetX, useOffsetY);
// translate to the bottom of the display
	m_camTranslate.setY(m_camTranslate.y() + screenEdges.y());
}

void OpenGL_ES_Render::resetTranslation(ScreenTransform const& st) {

}

Vector3 OpenGL_ES_Render::getCameraLocation(ScreenTransform const& st) const {
	const Vector2 screenEdges = st.screenSizeInPixel();

	Vector3 v3 = m_camTranslate;
	v3.setY(v3.y() - screenEdges.y());

	return st.screenToVector(v3);
}

void OpenGL_ES_Render::renderEnd(RenderState & state) {

#ifdef USE_ANDROID_OPENGL

// swapping is done by the GLView on Java
//eglSwapBuffers( state.m_display , state.m_surface);
//eglSwapBuffers( eglGetCurrentDisplay(), eglGetCurrentSurface( EGL_DRAW ) );
#else
	SDL_GL_SwapBuffers();
#endif

}

