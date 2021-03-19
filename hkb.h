/*
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
*/
#pragma once

#include "stdafx.h"

typedef HRESULT(__stdcall* TOPresentReturn)(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);
typedef HRESULT(__stdcall* TOResizeReturn) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

