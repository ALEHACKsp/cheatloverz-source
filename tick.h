/*
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
*/




#pragma once

#include "engine.h"
#include "CreateHook.h"
#include "hkcheat.h"
#include "GetSystemMetrics.h"
#include "hkpresent.h"

static const void* game_rbx_jmp;

void Tick(nk_command_buffer* b)
{
	if (!b) return;

	X = (float)iat(GetSystemMetrics)(SM_CXSCREEN);
	Y = (float)iat(GetSystemMetrics)(SM_CYSCREEN);

	Engine->SetBuffer(b);
	
	Engine->SetOverlaySize(X, Y);

	if (GetACheatLoverzKeyState((DWORD)VK_INSERT) == -32767) show_gui = !show_gui;

	HkPresent::Hook();

	Engine->SetBuffer(NULL);
}