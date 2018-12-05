#pragma once
#ifdef _WIN32
#include <Windows.h>

// Sets affinity to CPU 0
bool setAffinity()
{
	HANDLE proc_handle = GetCurrentProcess();
	DWORD_PTR proc_affinity_mask = 1;
	BOOL success = SetProcessAffinityMask(proc_handle, proc_affinity_mask);
	SetPriorityClass(proc_handle, THREAD_PRIORITY_TIME_CRITICAL);
	return success;
}

#endif
