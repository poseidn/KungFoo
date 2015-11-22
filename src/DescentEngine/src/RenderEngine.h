#pragma once

#include <boost/noncopyable.hpp>

#include <list>
#include <algorithm>

#include "Cpp11.h"
#include "VectorTypes.h"
#include "OpenGLInclude.h"

#include "Performance/SectionTimer.h"

#include "Visuals/ScreenTransform.h"

#include "InterfaceInitData.h"

#include "Visuals/SpriteVisual.h"
#include "Visuals/TextVisual.h"

//class SpriteVisual;
#include "Visuals/SpriteVisualList.h"
#include "Visuals/ParticleSystemVisualList.h"
#include "Visuals/ParticleSystemVisual.h"
#include "Visuals/TextVisualList.h"
#include "DataTypes/StaticVector.h"

// the render engine is never allowed to delete any visuals
// it can only remove them from its RenderLists. The entities holding the
// visuals are respnosible for deleting the actual objects
template<class OpenGLInterface, class OpenGLRender, class OpenGLState>
class RenderEngineAbstract: boost::noncopyable {
public:

	typedef OpenGLInterface interface_type;
	typedef OpenGLRender render_type;
	typedef OpenGLState state_type;

	RenderEngineAbstract();

	~RenderEngineAbstract();

	// todo: make thread safe so it can operate on the SpriteVisual list with call coming from the
	// logical thread
	SpriteVisualRef addSpriteVisual(SpriteVisual const& visual) {
		// todo: maybe use a presorted std::map here ?

		// make sure it is added according to it's position in the render queue
		auto lmdVisualPlacement = [&visual] (SpriteVisual const& listItem ) {
			// insert as position, as soon as higher prio items show up

				if ( visual.getPriority() < listItem.getPriority() ) {
					// already in an area which has too high prio for us ..
					return true;
				}
				else if ( visual.getPriority() == listItem.getPriority() ) {
					// sort by texture, cuts texture switching by 90%
					if ( visual.getTexture() == listItem.getTexture() ) {
						// found item with same texture, insert here
						return true;
					} else {
						// keep on searching
						return false;
					}
				}

				return false;
			};

		return m_spriteVisuals.push(visual, lmdVisualPlacement);
	}

	void addTextVisual(uniq<TextVisual> text) {
		m_textVisuals.push_front(std::move(text));
	}

	void removeTextVisual(TextVisual * text) {
		std::function<bool(uniq<TextVisual> &)> textLambda =
				[text]( uniq<TextVisual> & uTv)->bool {return text == uTv.get();};
		util::erase_if(m_textVisuals, textLambda);
	}

	void addParticleSystemVisual(uniq<ParticleSystemVisual> visual) {
		// todo: maybe use a presorted std::map here ?
		m_particleSystemVisuals.push_back(std::move(visual));
	}

// todo: make thread safe so it can operate on the SpriteVisual list with call coming from the
// logical thread
	void removeSpriteVisual(SpriteVisualRef visual, bool alsoDelete = false) {
		m_spriteVisuals.remove(visual);
	}

    void release() {
    	m_glInterface.release(m_glState);
    	m_isInitialized = false;
    }

	void render(float deltaT = 0.0f) {
		if (m_isInitialized == false)
			return;

		logging::DebugC<logging::Categories::RenderEngine>() << "RenderEngine: renderBegin";
		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.begin");
			m_glRenderer.renderBegin();
		}

		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.sprite_ingame");
			m_glRenderer.renderSpriteVisual(m_spriteVisuals, true, deltaT);
		}

		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.particle_manage");
			cleanParticleSystems();
			m_glRenderer.renderParticleSystemVisual(m_particleSystemVisuals);
		}

		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.text");
			// render text which is in game coordinates
			cleanTextVisual();
			m_glRenderer.renderTextVisual(m_textVisuals, true);
		}

		// reset how far the camera has already moved over the level !
		Vector3 curCam;
		//m_glRenderer.resetTranslation(getScreenTransform());
		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.cam_setup1");
			curCam = m_glRenderer.getCameraLocation(getScreenTransform());
			// don't use the render offset from the first tile to the left edge of the screen
			// this allows ui elemnts to be absolutely placed on-screen
			m_glRenderer.setCameraLocation(getScreenTransform(), Vector3(0.0f, 0.0f, 0.0f), false, false);
			// will use the parameter's which have been set via setCameraLocation
			m_glRenderer.renderSetupCam();
		}

		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.text_outgame");
			m_glRenderer.renderTextVisual(m_textVisuals, false);
		}
		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.sprite_outgame");
			m_glRenderer.renderSpriteVisual(m_spriteVisuals, false, deltaT);
		}

		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.cam_setup2");

			// restore old cam
			m_glRenderer.setCameraLocation(getScreenTransform(), curCam);
		}
		{
			SectionTimer secTime(GlobalTimingRepo::Rep, "render.end");
			m_glRenderer.renderEnd(m_glState);
		}
		logging::DebugC<logging::Categories::RenderEngine>() << "RenderEngine: renderEnd";

	}

	void clearSpriteList() {
		m_spriteVisuals.clear();
	}

	void init(typename OpenGLInterface::InterfaceDataType const& ifaceData) {
		if (m_isInitialized == true)
			return;
		m_glInterface.init(ifaceData, m_glState);
		m_isInitialized = true;
		std::cout << "render init done";
	}

	ScreenTransform
	const& getScreenTransform() const {
		return m_glInterface.getScreenTransform();
	}

// if set to Vector3, the f
	void setCameraLocation(Vector3 const& vec) {
		// todo: or make the camera setting a separete renderer pass
		m_glRenderer.setCameraLocation(m_glInterface.getScreenTransform(), vec);
	}

	Vector3 getCameraLocation() const {
		return m_glRenderer.getCameraLocation(m_glInterface.getScreenTransform());
	}

	void setDebugFaces(bool b) {
		m_glRenderer.setDebugFaces(b);
	}

	bool getDebugFaces() const {
		return m_glRenderer.getDebugFaces();
	}

	bool isInitialized() const {
		return m_isInitialized;
	}

	size_t getSpriteVisualCount() const {
		return m_spriteVisuals.activeSize();
	}

	size_t getSpriteVisualActiveCount() const {
		return m_spriteVisuals.activeCount();
	}

private:

	// erase all particles systems which are inactive
	void cleanParticleSystems() {
		std::function<bool(uniq<ParticleSystemVisual> &)> partRemove =
				[]( uniq<ParticleSystemVisual> & p ) -> bool {return p->toRemove();};
		util::erase_if(m_particleSystemVisuals, partRemove);
	}

	void cleanTextVisual() {
		std::function<bool(uniq<TextVisual> &)> textRemove =
				[]( uniq<TextVisual> & p ) -> bool {return p->toRemove();};
		util::erase_if(m_textVisuals, textRemove);
	}

	SpriteVisualSVector m_spriteVisuals;
	TextVisualListUniq m_textVisuals;

	ParticeSystemVisualListUniq m_particleSystemVisuals;

	OpenGLInterface m_glInterface;
	OpenGLRender m_glRenderer;
	OpenGLState m_glState;

	bool m_debugFaces = false;
	bool m_isInitialized = false;
}
;

#include "Common_OpenGL/OpenGL_ES_Render.h"

#ifdef USE_ANDROID_OPENGL

#include "Android_OpenGL/AndroidOpenGLESInterface.h"
#include "Android_OpenGL/AndroidOpenGLES_State.h"

class RenderEngine CPP11_FINAL : public RenderEngineAbstract<AndroidOpenGLESInterface, OpenGL_ES_Render,AndroidOpenGLES_State> {};

#else

#include "SDL_OpenGL/SDLOpenGLInterface.h"
#include "SDL_OpenGL/SDLOpenGL_State.h"

/*typedef RenderEngineAbstract<SDLOpenGLInterface, OpenGL_ES_Render,
 SDLOpenGL_State> RenderEngine;*/

// use no typedef to allow for forward declaration of this class
class RenderEngine CPP11_FINAL : public RenderEngineAbstract<SDLOpenGLInterface, OpenGL_ES_Render,
SDLOpenGL_State> {};
#endif

