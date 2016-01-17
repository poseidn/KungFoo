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
/*
 * disabled for the time being
 *

#include <functional>

#include "../Log.h"

#ifdef USE_THREADING_CPP11

// c++11 threading
#include <thread>
typedef std::thread PortableThread;

#endif

#ifdef USE_THREADING_NULL

class PortableThread {
public:

	template<typename _Callable, typename ... _Args>
	explicit PortableThread(_Callable&& __f, _Args&&... __args)
	{
		logging::Fatal() << "not impemented for Android yet";
	}
private:
};

#endif
*/
