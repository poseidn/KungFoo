#pragma once

#include <boost/noncopyable.hpp>
//#include "../Texture.h"
#include "../TextureRef.h"
#include "../VectorTypes.h"
#include "../OpenGLInclude.h"
#include "ScreenTransform.h"
#include "LayerPriority.h"
#include "VisualBase.h"
#include "DeferredVisualUpdate.h"

class SpriteVisual: public VisualBase {
public:
	enum {
		TextureCoordsSize = (4 * 2), VertexBufferSize = (4 * 3),
		// normals for each vertex needed
		NormalBufferSize = (3 * 4)
	};

	typedef GLfloat TextureCoordsArray[TextureCoordsSize];

	typedef GLfloat TextureCoordsArray4Frames[4][TextureCoordsSize];
	typedef GLfloat TextureCoordsArray8Frames[8][TextureCoordsSize];
	//typedef std::array<GLfloat, VertexBufferSize> VertexBufferArray;
	typedef GLfloat VertexBufferArray[VertexBufferSize];
	typedef GLfloat NormalBufferArray[NormalBufferSize];

	// for caching tests
	explicit SpriteVisual() :
			VisualBase() {
	}

	SpriteVisual(ScreenTransform const& trans, TexturePtr tex, Vector2 const& intialPosition,
			Vector2 const& size, LayerPriority prio);

	void setAnimated(float timeStep) {
		m_animated = true;
		m_stepTime = timeStep;
		m_nextStep = m_stepTime;
	}

	// todo: make this more generic and for all number of textures
	GLfloat const * getDefaultTextureCoordsPtr() const;

	DeferredVisualUpdate update(ScreenTransform const& trans, Vector2 const& pos);

	TexturePtr getTexture() const {
		return m_textureRef;
	}

	GLfloat const* getVertexBufferPtr() const {
		return m_vertexBuffer;
	}

	GLfloat const* getNormalBufferPtr() const {
		return m_defaultNormalBuffer;
	}

	VertexBufferArray const& getVertexBuffer() const {
		return m_vertexBuffer;
	}

	void step(float deltaT);

	void nextFrame();

	const static TextureCoordsArray m_defaultTextureCoords;
	const static TextureCoordsArray4Frames m_defaultTextureCoords4Frames;
	const static TextureCoordsArray8Frames m_defaultTextureCoords8Frames;
	const static NormalBufferArray m_defaultNormalBuffer;

	LayerPriority getPriority() const {
		return m_priority;
	}

	void reset() {
		m_currentFrame = 0;
	}

	// if true, the sprite will be rendered by the replacement introduced by the camera translation
	// if false, camera position is ignored. This is nice forui elements
	bool isIngame() const {
		return m_isIngame;
	}

	void setIngame(ScreenTransform const& trans, Vector2 const& vecPos, bool b) {
		m_isIngame = b;
		update(trans, vecPos);
		//std::cout << "m_vertexBuffer[0] = upperX; " << m_vertexBuffer[0] << std::endl;
	}


private:
	TexturePtr m_textureRef;
	VertexBufferArray m_vertexBuffer;
	Vector2 m_size;

	LayerPriority m_priority;

	unsigned char m_currentFrame;

	float m_stepTime;
	float m_nextStep;
};

