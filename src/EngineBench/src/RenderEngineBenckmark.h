#pragma once

#include <DescentEngine/src/RenderEngine.h>

class BenchState {
};

class BenchInterfaceInitData: public InterfaceInitData {

};

class BenchOpenGLInterface {
public:

	typedef BenchInterfaceInitData InterfaceDataType;

	void init(BenchInterfaceInitData const& data, BenchState & state) {
	}

	ScreenTransform const& getScreenTransform() const {
		return m_transform;
	}

private:
	ScreenTransform m_transform;
};

class Bench_Render: boost::noncopyable {
public:
	typedef BenchState RenderState;

	void renderBegin() {
	}

	void renderSpriteVisual(SpriteVisualSVector & ent, bool ingameSprite, float deltaT);

	void renderParticleSystemVisual(ParticeSystemVisualListUniq const& part) {
	}

	// ingameText are text visuals which are provided in game coordinates
	// rather than screen coordinates
	void renderTextVisual(TextVisualListUniq const& part, bool ingameText) {
	}

	void renderEnd(RenderState & state) {
	}

	void renderSetupCam() {
	}

	void resetTranslation(ScreenTransform const& st) {
	}

	// the tile at this coordinate will be displayed at the bottom left of the screen
	void setCameraLocation(ScreenTransform const& st, Vector3 vec, bool useOffsetX = true, bool useOffsetY =
			false) {
	}

	Vector3 getCameraLocation(ScreenTransform const& st) const {
		return Vector3(0, 0, 0);
	}

	void setDebugFaces(bool b) {
	}

	bool getDebugFaces() const {
		return false;
	}

};

class RenderEngineBenchmark CPP11_FINAL : public RenderEngineAbstract<BenchOpenGLInterface, Bench_Render,
		BenchState> {

};
