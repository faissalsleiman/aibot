/*
 * Windows generated DllMain.
 * Only compile and use this for windows.
 * Ignore for Linux and Unix
 */

// customTagLayer.cpp : Defines the entry point for the DLL application.
//
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

