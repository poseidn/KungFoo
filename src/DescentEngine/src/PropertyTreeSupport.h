#pragma once

#include "Log.h"
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>

typedef std::vector<std::string> stringvector;
typedef std::vector<double> doublevector;

class PropertyTreeSupport {
public:
	static stringvector GetAsStringList(boost::property_tree::ptree * propTree, std::string path,
			bool failIfNotFound = false) {
		stringvector fvec;
		try {
			for (boost::property_tree::ptree::value_type const& v : propTree->get_child(path)) {
				fvec.push_back(v.second.data());
			}
		} catch (boost::property_tree::ptree_bad_path & e) {
			// no problem, node optional ?
			if (failIfNotFound) {
				logging::Fatal() << "String list on path " << path
						<< " can not be found in configuration file";
			}

		}
		return fvec;
	}

	static doublevector GetAsDoubleList(boost::property_tree::ptree * propTree, std::string path) {
		doublevector fvec;
		try {
			for (boost::property_tree::ptree::value_type const& v : propTree->get_child(path)) {
				fvec.push_back(atof(v.second.data().c_str()));
			}
		} catch (boost::property_tree::ptree_bad_path & e) {
			// no problem, node optional
		}
		return fvec;
	}

	static doublevector GetAsDoubleList(boost::property_tree::ptree & propTree, std::string path) {
		doublevector fvec;
		try {
			for (boost::property_tree::ptree::value_type const& v : propTree.get_child(path)) {
				fvec.push_back(atof(v.second.data().c_str()));
			}
		} catch (boost::property_tree::ptree_bad_path & e) {
			// no problem, node optional
		}
		return fvec;
	}
};
