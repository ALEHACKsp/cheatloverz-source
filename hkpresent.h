/*
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_D3D11_IMPLEMENTATION
#define NK_IMPLEMENTATION
#define skCrypt(str) _xor_(str).c_str()
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>
#include <D3D11.h>
#include <d3dx11.h>
#include "skc.h"
#include <d3dx10.h>
#include <codecvt>
#include "render.h"
#include <Psapi.h>
#include <list>
#include <type_traits>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR
//ALLAHU AKBAR


inline const void* gadget(wchar_t* moduleName)
{
	static const void* jmprbx = nullptr;
	if (!jmprbx) {
		const auto ntdll = reinterpret_cast<const unsigned char*>(::GetModuleHandleW(moduleName));
		const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(ntdll);
		const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(ntdll + dos->e_lfanew);
		const auto sections = IMAGE_FIRST_SECTION(nt);
		const auto num_sections = nt->FileHeader.NumberOfSections;

		constexpr char section_name[5]{ '.', 't', 'e', 'x', 't' };
		const auto     section = std::find_if(sections, sections + num_sections, [&](const auto& s) {
			return std::equal(s.Name, s.Name + 5, section_name);
			});

		constexpr unsigned char instr_bytes[2]{ 0xFF, 0x26 };
		const auto              va = ntdll + section->VirtualAddress;
		jmprbx = std::search(va, va + section->Misc.VirtualSize, instr_bytes, instr_bytes + 2);
	}
	return jmprbx;
}

namespace detail
{
	extern "C" void* _spoofer_stub();

	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(
		const void* shell,
		Args... args
	) -> Ret
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper
	{
		// At least 5 params
		template<
			typename Ret,
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first,
				Second second,
				Third third,
				Fourth fourth,
				Pack... pack
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*,
				Pack...
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr,
				pack...
				);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<
			typename Ret,
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first = First{},
				Second second = Second{},
				Third third = Third{},
				Fourth fourth = Fourth{}
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr
				);
		}
	};
}


template <typename Ret, typename... Args>
static inline auto spoof_call(
	const void* trampoline,
	Ret(*fn)(Args...),
	Args... args
) -> Ret
{
	struct shell_params
	{
		const void* trampoline;
		void* function;
		void* rdx;
	};

	shell_params p{ trampoline, reinterpret_cast<void*>(fn) };
	using mapper = detail::argument_remapper<sizeof...(Args), void>;
	return mapper::template do_call<Ret, Args...>((const void*)&detail::_spoofer_stub, &p, args...);
}


#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "d3d11.lib")
bool hidden_window = false;
bool finished_window = false;
bool show_gui = true;
static ID3D11DeviceContext* m_pContext;
static ID3D11RenderTargetView* g_pRenderTargetView;
static IDXGISwapChain* g_pSwapChain;

static WNDPROC oWndProc;

static bool firstTime = true;
static ID3D11Device* uDevice;
nk_context* g_pNkContext;
static nkDraw* Engine = new nkDraw();
using f_present = HRESULT(__stdcall*)(IDXGISwapChain* pthis, UINT sync_interval, UINT flags);
f_present SwapChain = nullptr;
#include "stdafx.h"
#include "tick.h"

#include "engine.h"
#include "style.c"

enum theme { THEME_BLACK, THEME_WHITE, THEME_RED, THEME_BLUE, THEME_DARK, THEME_PURPLE, CHEATLOVERZ };
static void
set_style(struct nk_context* ctx, enum theme theme)
{
	struct nk_color table[NK_COLOR_COUNT];
	if (theme == THEME_WHITE) {
		//ctx->style.edit.rounding = 5;
		table[NK_COLOR_TEXT] = nk_rgba(70, 70, 70, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_HEADER] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_BORDER] = nk_rgba(0, 0, 0, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(185, 185, 185, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(170, 170, 170, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(160, 160, 160, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(150, 150, 150, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(120, 120, 120, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_SELECT] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(80, 80, 80, 255);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(70, 70, 70, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(60, 60, 60, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_EDIT] = nk_rgba(150, 150, 150, 255);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(0, 0, 0, 255);
		table[NK_COLOR_COMBO] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_CHART] = nk_rgba(160, 160, 160, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(45, 45, 45, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(180, 180, 180, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(140, 140, 140, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(150, 150, 150, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(160, 160, 160, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(180, 180, 180, 255);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_RED) {
		table[NK_COLOR_TEXT] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(30, 33, 40, 215);
		table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
		table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
		nk_style_from_table(ctx, table);
	}
	else if (theme == CHEATLOVERZ) {
		table[NK_COLOR_TEXT] = nk_rgba(20, 20, 20, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(202, 212, 214, 215);
		table[NK_COLOR_HEADER] = nk_rgba(137, 224, 144, 220);
		table[NK_COLOR_BORDER] = nk_rgba(140, 173, 147, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(137, 224, 150, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(142, 229, 162, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(147, 234, 151, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(177, 210, 210, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(182, 215, 215, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(137, 224, 170, 255);
		table[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(177, 210, 192, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_EDIT] = nk_rgba(210, 210, 210, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
		table[NK_COLOR_COMBO] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_CHART] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(190, 200, 200, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_PURPLE)
	{
		table[NK_COLOR_TEXT] = nk_rgba(255, 132, 59, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(14, 0, 14, 0.9);
	}
}
typedef int (WINAPI* LPFN_MBA)(DWORD);
static LPFN_MBA GetACheatLoverzKeyState;

#include "setting.h"
namespace HkPresent {
	void InitFont()
	{
	}
	float xfloat(int a)
	{
		return a + 60;
	}
	void ShowMenu()
	{


	}
	void Hook()
	{
		// menu here

	}
}
uintptr_t p1337(uintptr_t moduleAdress, const char* signature)
{
	static auto patternToByte = [](const char* pattern)
	{
		auto       bytes = std::vector<int>{};
		const auto start = const_cast<char*>(pattern);
		const auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else { bytes.push_back(strtoul(current, &current, 16)); }
		}
		return bytes;
	};

	const auto dosHeader = (PIMAGE_DOS_HEADER)moduleAdress;
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)moduleAdress + dosHeader->e_lfanew);

	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto       patternBytes = patternToByte(signature);
	const auto scanBytes = reinterpret_cast<std::uint8_t*>(moduleAdress);

	const auto s = patternBytes.size();
	const auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i)
	{
		bool found = true;
		for (auto j = 0ul; j < s; ++j)
		{
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}
		if (found) { return reinterpret_cast<uintptr_t>(&scanBytes[i]); }
	}
	return NULL;
}
uintptr_t discmodule()
{
	static uintptr_t discordModuleBase = 0;

	if (!discordModuleBase)
		discordModuleBase = (uintptr_t)GetModuleHandleA("DiscordHook64.dll");

	return discordModuleBase;
}
short GetViperKeyState(const int vKey)
{
	static uintptr_t addrGetAsyncKeyState = NULL;

	if (!addrGetAsyncKeyState)
		addrGetAsyncKeyState = p1337(discmodule(), ("40 53 48 83 EC 20 8B D9 FF 15 ? ? ? ?"));

	if (!addrGetAsyncKeyState)
		return false;

	using GetAsyncKeyState_t = short(__fastcall*)(int);
	auto fnGetAyncKeyState = (GetAsyncKeyState_t)addrGetAsyncKeyState;

	return (fnGetAyncKeyState, vKey);
}

HRESULT __stdcall hk_present(IDXGISwapChain* pthis, UINT sync_interval, UINT flags)
{
	ID3D11Texture2D* pRenderTargetTexture;
	g_pSwapChain = nullptr;

	g_pSwapChain = pthis;

	if (firstTime) {

		pthis->GetDevice(__uuidof(ID3D11Device), (void**)&uDevice);

		if (!uDevice) return false;

		uDevice->GetImmediateContext(&m_pContext);

		if (!m_pContext) return false;

		g_pNkContext = nk_d3d11_init((ID3D11Device*)uDevice, (int)iat(GetSystemMetrics)(SM_CXSCREEN), (int)iat(GetSystemMetrics)(SM_CYSCREEN), (unsigned int)MAX_VERTEX_BUFFER, (unsigned int)MAX_INDEX_BUFFER);
		{
			nk_d3d11_font_stash_begin(&Engine->atlas);
			nk_d3d11_font_stash_end();

			Engine->CopyContext = g_pNkContext;
		}

		if (SUCCEEDED(pthis->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)))
		{
			uDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView);
			pRenderTargetTexture->Release();
			uDevice->Release();
		}

		firstTime = false;
	}

	if (!g_pRenderTargetView)
	{
		pthis->GetDevice(__uuidof(ID3D11Device), (void**)&uDevice);

		if (!uDevice) return false;

		uDevice->GetImmediateContext(&m_pContext);

		if (!m_pContext) return false;

		if (SUCCEEDED(pthis->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)))
		{
			uDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView);
			pRenderTargetTexture->Release();
			uDevice->Release();
		}
	}

	if (g_pRenderTargetView)
	{
		m_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

		nk_input_end(g_pNkContext);
		HkPresent::ShowMenu();
		nk_input_begin(g_pNkContext);


		nk_font_atlas* atlas;
		nk_d3d11_font_stash_begin(&atlas);
		struct nk_font* font;
		const char* font_path = skCrypt("C:\\Windows\\Fonts\\Verdana.ttf");
		font = nk_font_atlas_add_from_file(atlas, font_path, 16.0f, NULL);
		nk_d3d11_font_stash_end();
		nk_init_default(g_pNkContext, &font->handle);
		hidden_window = 1;

		nk_begin(g_pNkContext, skCrypt(" "), nk_rect(1, 1, 1, 1), NK_WINDOW_MINIMIZED);

		nk_end(g_pNkContext);

		nk_d3d11_render(m_pContext, NK_ANTI_ALIASING_ON);
	}
	return SwapChain(pthis, sync_interval, flags);
}

LRESULT CALLBACK hkWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_SIZE:
		UINT width = LOWORD(lparam);
		UINT height = HIWORD(lparam);

		ID3D11Texture2D* back_buffer;
		D3D11_RENDER_TARGET_VIEW_DESC desc;
		HRESULT hr;

		if (g_pRenderTargetView)
		{
			g_pRenderTargetView->Release();
			g_pRenderTargetView = nullptr;
		}

		if (m_pContext)
		{
			m_pContext->OMSetRenderTargets(0, NULL, NULL);
			if (g_pSwapChain)
				g_pSwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

			nk_d3d11_resize(m_pContext, (int)width, (int)height);
		}
		break;
	}

	nk_d3d11_handle_event(hwnd, msg, wparam, lparam);

	return CallWindowProcW(oWndProc, hwnd, msg, wparam, lparam);
}