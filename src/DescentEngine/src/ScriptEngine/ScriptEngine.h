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

class ResourceEngine;

class ScriptEngine : boost::noncopyable {
public:
	ScriptEngine(ResourceEngine & re) {}
};

/*
 *
 * LUA ScriptEngine is diasbled for the time being
 *
#include <memory>
#include <list>

#include <boost/noncopyable.hpp>

#include "../Cpp11.h"
#include "../Log.h"

extern "C" {
#include "lua.h"
}

#include <luabind/luabind.hpp>

// hot - swapping in lua, just reload the the module
//#define DESCENT_FILE_WATCH 1

#ifdef DESCENT_FILE_WATCH
#include <inotify-cxx.h>
typedef std::shared_ptr<InotifyWatch> InotifyWatchPtr;
#endif

class ResourceEngine;
class ScriptEngine;

class Script {
public:

	ScriptEngine * m_scriptEngine;
	lua_State * m_luaState = nullptr;

	template<class ... TParams>
	void callFunction(std::string const& functionName, TParams ... params) {
		checkWatch();

		if (m_inactive)
			return;

		try {
			luabind::call_function<int>(m_luaState, functionName.c_str(), params...);
		} catch (luabind::error e) {
			logging::Info() << " Lua exception:" << logging::NewLine << "\t" << e.what() << logging::NewLine
					<< " In file: " << m_fileName << logging::NewLine << " In call: " << functionName;
			m_inactive = true;
		}
	}

	void checkWatch();

	std::string m_fileName;
	std::string m_scriptName;

	// script can become inactive, if its execution failed once
	bool m_inactive = false;

#ifdef DESCENT_FILE_WATCH
	InotifyWatchPtr m_inotifyWatch;
#endif
};

class LuaLogging {
public:

	void Info(const std::string& s) {
		logging::Info() << s;
	}

	void Fatal(const std::string& s) {
		logging::Fatal() << s;
	}
};

class ScriptEngine: boost::noncopyable {
public:

	typedef std::function<void(lua_State *)> ObjectRegisterLambda;
	typedef std::list<ObjectRegisterLambda> RegisterList;

	ScriptEngine(ResourceEngine & re);
	~ScriptEngine();

	Script loadScript(std::string const& scriptName);

	void checkWatch(Script & sc);

	void addObjectRegister(ObjectRegisterLambda const & reg);

private:

	void registerWatch(std::string const& filePath, Script & sc);

	void bootstrapState(Script & sc);
	void bootstrapScript(Script & sc, std::string const& code);

	void injectScript(Script & sc);

	lua_State * m_defaultState;

	ResourceEngine & m_re;
	RegisterList m_registerList;

#ifdef DESCENT_FILE_WATCH
	Inotify m_inotify;
	std::list < InotifyWatchPtr> m_watches;
#endif
};
*/
