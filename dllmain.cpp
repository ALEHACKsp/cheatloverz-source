/*
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
*/



#include "stdafx.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
		DisableThreadLibraryCalls(hModule);
		Hooks::Start();
    }

    return TRUE;
}

