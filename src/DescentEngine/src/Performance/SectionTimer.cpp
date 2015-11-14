#include "SectionTimer.h"

SectionRepo GlobalTimingRepo::Rep;

#ifdef DESCENT_PROFILE

#include <iomanip>
#include <fstream>

void SectionRepo::storeResult(std::string const& name, Duration dr) {
	m_durations[name].push( dr );
}

void SectionRepo::report() {
	size_t overallMs = 0;
	for (auto const& it : m_durations) {
		if ( it.second.hasEntries()) {
			overallMs += it.second.last().count();
		}
	}

	for (auto const& it : m_durations) {
		if ( it.second.hasEntries()) {
			const float ratioOfAll = float(it.second.last().count()) / float(overallMs);
			logging::Info() << std::setprecision(2) << "Comp: " << it.first << "\t\t" << ratioOfAll
			<< " :: " << it.second.last().count();
		}
	}

	logging::Info() << logging::NewLine << "Overtime time (mu sec) " << overallMs << " fps: "
	<< 1.0f / (float(overallMs) / 1000000.0f);
}

void SectionRepo::clearFile( std::string const& filename) {
	std::ofstream ofs (filename, std::ofstream::out | std::ofstream::trunc );
	ofs.close();
}

void SectionRepo::dumpFile( std::string const& filename) {
	std::ofstream ofs (filename, std::ofstream::out | std::ofstream::app);
	if (!ofs) {
		logging::Error() << "Cannot open file " << filename << " to dump performance data";
		return;
	}
	for (auto const& it : m_durations) {
		ofs << it.first;
		for (int i = -it.second.size()+1; i <= 0; i++ ) {
			// 0 gives the most recent added , -n the n-th recent
			ofs << ":" << it.second.get(i).count();
		}
		ofs << std::endl;
	}
	ofs.close();
}

void SectionRepo::clear() {
	m_durations.clear();
}

#endif
