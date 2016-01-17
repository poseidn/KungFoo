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
