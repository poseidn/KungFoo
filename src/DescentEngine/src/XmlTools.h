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

#include <boost/algorithm/string/split.hpp>
#include <string>
#include <array>
#include <regex>
#include <tinyxml2.h>
#include "VectorTypes.h"

namespace XmlTools {

inline std::vector<std::string> parseStringList(std::string const& inpConst) {
	std::vector < std::string > res;
	std::string inp(inpConst);
	typedef boost::split_iterator<std::string::iterator> string_split_iterator;

	for (auto It = boost::make_split_iterator(inp, first_finder(",", boost::is_iequal()));
			It != string_split_iterator(); ++It) {
		std::string num = boost::copy_range<std::string>(*It);
		res.push_back(num);
	}

	return res;
}

inline Vector2 parseVector2(std::string const& inpConst) {
	std::string inp(inpConst);
	std::array<float, 2> vecNum;
	size_t i = 0;
	typedef boost::split_iterator<std::string::iterator> string_split_iterator;

	for (auto It = boost::make_split_iterator(inp, first_finder(",", boost::is_iequal()));
			It != string_split_iterator(); ++It) {
		std::string num = boost::copy_range<std::string>(*It);
		std::stringstream streamNum(num);
		float f;
		streamNum >> f;
		assert(i < vecNum.size());
		vecNum[i] = f;
		i++;
	}

	return Vector2(vecNum[0], vecNum[1]);
}

inline Vector2 readVector2(tinyxml2::XMLElement * elem, std::string const& attribName,
		Vector2 const& defaultValue) {
	assert(elem);
	const char * val = elem->Attribute(attribName.c_str());
	if (val != nullptr) {
		const std::string valStr(val);
		return parseVector2(valStr);
	} else {
		return defaultValue;
	}
}

inline int readInt(tinyxml2::XMLElement * elem, std::string const& attribName, int defaultValue) {
	assert(elem);
	const char * val = elem->Attribute(attribName.c_str());
	if (val != nullptr) {
		std::stringstream streamNum(val);
		int i;
		streamNum >> i;
		return i;
	} else {
		return defaultValue;
	}
}

inline std::string readString(tinyxml2::XMLElement * elem, std::string const& attribName) {
	assert(elem);
	const char * val = elem->Attribute(attribName.c_str());
	if (val != nullptr) {
		return std::string(val);
	} else {
		logging::Fatal() << "Attribute " << attribName << " not found";
		return "";
	}
}

inline std::string readString(tinyxml2::XMLElement * elem, std::string const& attribName,
		std::string const& defaultValue) {
	assert(elem);
	const char * val = elem->Attribute(attribName.c_str());
	if (val != nullptr) {
		return std::string(val);
	} else {
		return defaultValue;
	}
}

inline bool readBool(tinyxml2::XMLElement * elem, std::string const& attribName, bool defaultBool) {
	std::stringstream boolStr;
	boolStr << defaultBool;
	logging::Fatal() << "not implemented";
//return (readString(elem, attribName, boolStr.str()) == "1");
	return false;
}

}
