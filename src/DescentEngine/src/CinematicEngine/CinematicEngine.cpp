#include "CinematicEngine.h"

#include "../SoundEngine/SoundEngine.h"
#include "../ResourceEngine/ResourceEngine.h"
#include "../EntityEngine/EntityEngine.h"
#include "../AnimationEngine/AnimationEngine.h"
#include "../AnimationEngine/EntityAnimation.h"
#include "../Engines.h"

void CinematicSound::execute(Engines & eg) {
	auto snd = eg.resourceEngine().loadSound(m_soundName);
	eg.soundEngine().playSound(snd, 0.0f);
}

CinematicTransformAnimation::CinematicTransformAnimation(std::string const& entityName, Vector2 const& start,
		Vector2 final, CinematicTimespan span) :
		CinematicBase(span), m_entityName(entityName), m_start(start), m_final(final) {

}

void CinematicTransformAnimation::execute(Engines & eg) {
	auto ent = eg.entityEngine().getEntity(m_entityName);
	assert(ent);

	eg.animationEngine().addEntityAnimation(
			std14::make_unique<EntityAnimation<TransformLocation>>(*ent,
					TransformLocation(m_start, m_final, m_span.getDuration())));
}

CinematicTranspararencyAnimation::CinematicTranspararencyAnimation(std::string const& entityName, float start,
		float final, CinematicTimespan span) :
		CinematicBase(span), m_entityName(entityName), m_start(start), m_final(final) {

}

void CinematicTranspararencyAnimation::execute(Engines & eg) {
	auto ent = eg.entityEngine().getEntity(m_entityName);
	assert(ent);

	eg.animationEngine().addEntityAnimation(
			std14::make_unique<EntityAnimation<TransformTransparency> >(*ent,
					TransformTransparency(m_start, m_final, m_span.getDuration())));
}

CinematicEngine::CinematicEngine(Engines & eng) :
		m_engines(eng), m_currentTick(0.0f) {
}

void CinematicEngine::step(float deltaT) {
	if (m_timeline.size() == 0)
		return;
	// check for the next cinematic to run !
	m_currentTick += deltaT;

	std::vector < CinematicTimeline::iterator > toRemove;

	// assumes that the std::map is sorted by smallest entry first
	auto next = m_timeline.begin();
	while (next != m_timeline.end()) {
		if (next->first < m_currentTick) {
			logging::Debug() << "Executing Cinematic part";
			next->second->execute(m_engines);
			toRemove.push_back(next);
			next++;
		} else {
			// jump to end to quit the loop
			next = m_timeline.end();
		}
	}

	// remove all cinematics which have been flagged
	for (auto mapIt : toRemove) {
		m_timeline.erase(mapIt);
	}
}

void CinematicEngine::addTimelineItem(CinematicBasePtr cn) {
	m_timeline[cn->getTimespan().getStart()] = cn;
}

// resets the timeline to start from 0 again
void CinematicEngine::reset() {
	m_currentTick = 0.0f;
}
