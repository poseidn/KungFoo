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

