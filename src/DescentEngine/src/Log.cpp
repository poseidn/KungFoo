#include "Log.h"


#ifdef DESCENT_WIN_COMPILE
#include <Windows.h>

void logging::_internal_windows_log(std::string message, logging::MessageLevel lvl)
{
	OutputDebugString(message.c_str());	
	OutputDebugString("\n");
}
#else 
void logging::_internal_windows_log(std::string message, logging::MessageLevel lvl)
{
}
#endif
