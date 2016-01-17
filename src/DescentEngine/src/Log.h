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

#if defined(STUCK_MSVC_COMPILE)
#include <Windows.h>
#endif

#ifdef USE_ANDROID
#include <android/log.h>
#define ANDROID_LOGI( cstr ) ((void)__android_log_print(ANDROID_LOG_INFO, "FastDescent", "%s", cstr ))
#define ANDROID_LOGW( cstr ) ((void)__android_log_print(ANDROID_LOG_WARN, "FastDescent", "%s", cstr ))
#define ANDROID_LOGE( cstr ) ((void)__android_log_print(ANDROID_LOG_ERROR, "FastDescent", "%s", cstr ))
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include "Cpp11.h"

namespace logging {

static const std::string NewLine = "\n";

enum class MessageLevel {
	Debug, Normal, Error, Fatal
};

#define DESCENT_LOG_FILENAME "descent.log"

void _internal_windows_log(std::string message, MessageLevel lvl);

inline void _internal_log(std::string message, MessageLevel lvl) {
#ifdef USE_ANDROID

	if ( ( lvl == MessageLevel::Fatal ) || (lvl == MessageLevel::Error) ) {
		ANDROID_LOGE ( message.c_str());
	}
	else {
		ANDROID_LOGI ( message.c_str());
	}
#else
	std::cout << message << std::endl;
#ifdef DESCENT_WIN_COMPILE
	_internal_windows_log(message, lvl);
#endif
	std::ofstream outFile(DESCENT_LOG_FILENAME, std::ios::app);
	outFile << message << std::endl;
	outFile.close();
#endif
}

inline void resetLogFile() {
	// will empty the file
	std::ofstream outFile(DESCENT_LOG_FILENAME, std::ios::trunc);
	outFile.close();
}

namespace Categories {
class Collision {
public:
	static CPP11_CONSTEXPR size_t isEnabled = 1;
};

class GameLoop {
public:
	static CPP11_CONSTEXPR size_t isEnabled = 1;
};

class RenderEngine {
public:
	static CPP11_CONSTEXPR size_t isEnabled = 1;
};

class Default {
public:
	static CPP11_CONSTEXPR size_t isEnabled = 1;
};
}

template<MessageLevel TLevel, class TLogCategory = Categories::Default>
class LogImplBase {
public:
	explicit LogImplBase() {
	}

	~LogImplBase() {
		//if (TLogCategory::isEnabled)
			_internal_log(m_stream.str(), TLevel);
		assert(TLevel != MessageLevel::Fatal);
	}

	template<class T>
	LogImplBase &
	operator<<(T const & t) {
		if (TLogCategory::isEnabled)
			m_stream << t;
		return *this;
	}

protected:
	LogImplBase(LogImplBase const&);
	LogImplBase& operator=(LogImplBase);
	std::stringstream m_stream;
	MessageLevel m_msgLevel;
};

// performs no logging
// gets optimized out by compiler
template<MessageLevel TLevel, class TLogCategory = Categories::Default>
class LogNullBase {
public:
	explicit LogNullBase() {
	}

	template<class T>
	LogNullBase &
	operator<<(T const & t) {
		return *this;
	}
};

#ifdef DESCENT_LOG_ENABLED

using Info = LogImplBase< MessageLevel::Normal, Categories::Default>;
template<typename TCat>
using InfoC = LogImplBase< MessageLevel::Normal, TCat >;
/*
 using Debug = LogImplBase< MessageLevel::Debug, Categories::Default>;
 template<typename TCat>
 using DebugC = LogImplBase< MessageLevel::Debug, TCat >;
 */
using Debug = LogNullBase< MessageLevel::Debug, Categories::Default>;
template<typename TCat>
using DebugC = LogNullBase< MessageLevel::Debug, TCat >;

using Error = LogImplBase<MessageLevel::Error,Categories::Default>;
using Fatal = LogImplBase<MessageLevel::Fatal,Categories::Default>;

class NotImplemented: Fatal {
public:
	explicit NotImplemented() {
		this->m_stream << "Method not implemented";
	}
};

#else

// disable all logging, these templates will be completely removed by
// the optimizer
// the fatal loggings will still be regular
using Info = LogNullBase< MessageLevel::Normal, Categories::Default>;
template<typename TCat>
using InfoC = LogNullBase< MessageLevel::Normal, TCat >;

using Debug = LogNullBase< MessageLevel::Debug, Categories::Default>;
template<typename TCat>
using DebugC = LogNullBase< MessageLevel::Debug, TCat >;

using Error = LogNullBase<MessageLevel::Error,Categories::Default>;
using Fatal = LogImplBase<MessageLevel::Fatal,Categories::Default>;

using NotImplemented = Fatal;

#endif

}
