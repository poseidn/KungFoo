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
 #ifdef USE_THREADING_PTHREAD
 */
// will use pthreads, but disabled for the time being
/*class PortableMutex {
public:
	PortableMutex() {

		pthread_mutex_init(&m_mutex, NULL);
	}

	~PortableMutex() {
		pthread_mutex_destroy(&m_mutex);
	}

	void lock() {
		pthread_mutex_lock(&m_mutex);
	}

	void unlock() {
		pthread_mutex_unlock(&m_mutex);
	}

private:
	pthread_mutex_t m_mutex;
};*/
/*
 #endif

 #ifdef USE_THREADING_CPP11
 */
// c++11 threading
/*#include <mutex>
 typedef std::mutex PortableMutex;*/
/*
 #endif

 #ifdef USE_THREADING_NULL

 class PortableMutex {
 public:
 PortableMutex() {

 }

 ~PortableMutex() {
 }

 void lock() {

 }

 void unlock() {
 }
 };

 #endif*/

