#pragma once

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <utility>

#include "../Cpp11.h"
#include "../VectorTypes.h"
#include "../Log.h"

class Engines;
class SpriteVisual;

typedef float CinematicTimepoint;

class CinematicTimespan {
public:
	CinematicTimespan(float start, float end) :
			m_start(start), m_end(end) {

	}

	float getDuration() const {
		return m_end - m_start;
	}

	float getStart() const {
		return m_start;
	}

private:
	float m_start;
	float m_end;
};

// todo: animation system could also use a integer timing system to be faster and save memory...
class CinematicBase: boost::noncopyable {
public:
	CinematicBase(CinematicTimespan span) :
			m_span(span) {
	}

	virtual void execute(Engines & eg) = 0;

	CinematicTimespan const& getTimespan() const {
		return m_span;
	}

protected:
	CinematicTimespan m_span;
};

typedef std::shared_ptr<CinematicBase> CinematicBasePtr;

class CinematicTransformAnimation: public CinematicBase {
public:
	CinematicTransformAnimation(std::string const& entityName, Vector2 const& start, Vector2 final,
			CinematicTimespan span);
	virtual void execute(Engines & eg) CPP11_OVERRIDE;

private:
	std::string m_entityName;
	Vector2 m_start;
	Vector2 m_final;

};

class CinematicTranspararencyAnimation: public CinematicBase {
public:
	CinematicTranspararencyAnimation(std::string const& entityName, float start, float final,
			CinematicTimespan span);

	virtual void execute(Engines & eg) CPP11_OVERRIDE;

private:
	std::string m_entityName;
	float m_start;
	float m_final;
};

class CinematicLambda: public CinematicBase {
public:

	typedef std::function<void(Engines &)> TimedLambda;

	CinematicLambda(TimedLambda lmd, CinematicTimepoint start) :
			CinematicBase(CinematicTimespan(start, start)), m_lmd(lmd) {

	}

	virtual void execute(Engines & eg) CPP11_OVERRIDE {
		m_lmd(eg);
	}

private:
	TimedLambda m_lmd;
};

class CinematicSound: public CinematicBase {
public:
	CinematicSound(std::string const& soundName, CinematicTimepoint start) :
			CinematicBase(CinematicTimespan(start, start)), m_soundName(soundName) {

	}

	virtual void execute(Engines & eg) CPP11_OVERRIDE;

private:
	std::string m_soundName;
};

typedef std::map<float, CinematicBasePtr> CinematicTimeline;

class CinematicEngine: boost::noncopyable {
public:
	CinematicEngine(Engines & eng);
	~CinematicEngine() {
	}

	void step(float deltaT);

	void addTimelineItem(CinematicBasePtr cn);

	// resets the timeline to start from 0 again
	void reset();

	Engines & getEngines() {
		return m_engines;
	}

private:
	Engines & m_engines;
	CinematicTimeline m_timeline;
	float m_currentTick;
};
