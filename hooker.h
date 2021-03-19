/*
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
ALLAH AKBAR
*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "skc.h"
#include <vector>
#include <psapi.h>
#include <stdio.h>
#include <Windows.h>
#include <psapi.h>
#include <intrin.h>

#include <string>
#include <vector>
#include <TlHelp32.h>
#include <xstring>
#include "data.h"
#include <winscard.h>
#include <iosfwd>

#include <vector>
#include <d3dx9math.h>
#include <set>
#include <string>
#include <windows.h>
#include <ctype.h>
#include <iostream>
#include "hkpresent.h"
#include <vector>
#include "hkscene.h"
#define M_PI	3.14159265358979323846264338327950288419716939937510

ID3D11Device* pD11Device = nullptr;
ID3D11DeviceContext* pD11DeviceContext = nullptr;
ID3D11RenderTargetView* pD11RenderTargetView = nullptr;
#include "offset.h"

#define RELATIVE_ADDR(addr, size) ((PBYTE)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))

#define ReadPointer(base, offset) (*(PVOID *)(((PBYTE)base + offset)))
#define ReadDWORD(base, offset) (*(PDWORD)(((PBYTE)base + offset)))
#define ReadBYTE(base, offset) (*(((PBYTE)base + offset)))

HWND GameWindow;
namespace memory {
	uintptr_t occurence(const char* module, const char* pattern) {

#define in_range(x, a, b) (x >= a && x <= b)
#define get_bits(x) (in_range((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA): (in_range(x, '0', '9') ? x - '0': 0))
#define get_byte(x) (get_bits(x[0]) << 4 | get_bits(x[1]))

		MODULEINFO mod;
		iat(K32GetModuleInformation).get()(iat(GetCurrentProcess).get()(), iat(GetModuleHandleA).get()(module), &mod, sizeof(MODULEINFO));
		uintptr_t start = (uintptr_t)mod.lpBaseOfDll;
		uintptr_t end = (uintptr_t)mod.lpBaseOfDll + (uintptr_t)mod.SizeOfImage;
		uintptr_t match = (uintptr_t)nullptr;
		const char* current = pattern;

		for (uintptr_t pCur = start; pCur < end; pCur++) {

			if (!*current)
				return match;

			if (*(PBYTE)current == ('\?') || *(BYTE*)pCur == get_byte(current)) {
				if (!match)
					match = pCur;

				if (!current[2])
					return match;

				if (*(PWORD)current == ('\?\?') || *(PBYTE)current != ('\?'))
					current += 3;
				else
					current += 2;
			}
			else {
				current = pattern;
				match = 0;
			}
		}
		return (uintptr_t)nullptr;
	}

	inline uintptr_t dereference(uintptr_t address, unsigned int offset)
	{
		if (address == 0)
			return (uintptr_t)nullptr;

		if (sizeof(uintptr_t) == 8)
			return address + (int)((*(int*)(address + offset) + offset) + sizeof(int));

		return *(uintptr_t*)(address + offset);
	}

}
namespace Utilities {
	VOID CreateConsole() {
		AllocConsole();
		static_cast<VOID>(freopen("CONIN$", "r", stdin));
		static_cast<VOID>(freopen("CONOUT$", "w", stdout));
		static_cast<VOID>(freopen("CONOUT$", "w", stderr));
	}


	BOOLEAN MaskCompare(PVOID buffer, LPCSTR pattern, LPCSTR mask) {
		for (auto b = reinterpret_cast<PBYTE>(buffer); *mask; ++pattern, ++mask, ++b) {
			if (*mask == 'x' && *reinterpret_cast<LPCBYTE>(pattern) != *b) {
				return FALSE;
			}
		}

		return TRUE;
	}

	PBYTE FindPattern(PVOID base, DWORD size, LPCSTR pattern, LPCSTR mask) {
		size -= static_cast<DWORD>(strlen(mask));

		for (auto i = 0UL; i < size; ++i) {
			auto addr = reinterpret_cast<PBYTE>(base) + i;
			if (MaskCompare(addr, pattern, mask)) {
				return addr;
			}
		}

		return NULL;
	}
	PBYTE FindPattern(LPCSTR pattern, LPCSTR mask) {
		MODULEINFO info = { 0 };
		K32GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));

		return FindPattern(info.lpBaseOfDll, info.SizeOfImage, pattern, mask);
	}
}namespace MemoryHelper
{
	namespace Pattern
	{
		uintptr_t PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex = 0);
		uintptr_t PatternScan(const char* sSignature, size_t nSelectResultIndex = 0);
	}

	void Log(const char* sFilePath, char const* const sFormat, ...);
}

uintptr_t MemoryHelper::Pattern::PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex)
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
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto       patternBytes = patternToByte(sSignature);
	const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

	const auto s = patternBytes.size();
	const auto d = patternBytes.data();

	size_t nFoundResults = 0;

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

		if (found)
		{
			if (nSelectResultIndex != 0)
			{
				if (nFoundResults < nSelectResultIndex)
				{
					nFoundResults++;                                   // Skip Result To Get nSelectResultIndex.
					found = false;                                     // Make sure we can loop again.
				}
				else
				{
					return reinterpret_cast<uintptr_t>(&scanBytes[i]);  // Result By Index.
				}
			}
			else
			{
				return reinterpret_cast<uintptr_t>(&scanBytes[i]);      // Default/First Result.
			}
		}
	}

	return NULL;
}




uintptr_t MemoryHelper::Pattern::PatternScan(const char* sSignature, size_t nSelectResultIndex)
{
	static bool bIsSetted = false;

	static MODULEINFO info = { 0 };

	if (!bIsSetted)
	{
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));
		bIsSetted = true;
	}

	return ((uintptr_t)info.lpBaseOfDll, sSignature, nSelectResultIndex);
}
bool InitGetKeys()
{
	HMODULE API = GetModuleHandleW(skCrypt(TEXT("win32u.dll")));
	if (API != NULL)
	{
		GetACheatLoverzKeyState = (LPFN_MBA)GetProcAddress(API, skCrypt("NtUserGetAsyncKeyState"));
		if (GetACheatLoverzKeyState != NULL)
			return true;
		else
			return false;
	}
}

uintptr_t PatternScan(uintptr_t moduleAdress, const char* signature)
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
namespace Hooking
{
	uintptr_t GetDiscordModuleBase();
	uintptr_t GetSceneAddress();

	short GetAsyncKeyState(const int vKey);

	bool InsertHook(uintptr_t pOriginal, uintptr_t pHookedFunction, uintptr_t pOriginalCall);
	bool RemoveHook(uintptr_t pOriginal);

	bool CreateHook(uintptr_t pOriginal, uintptr_t pHookedFunction, uintptr_t pOriginalCall);
	bool EnableHook(uintptr_t pTarget, bool bIsEnabled);
	bool EnableHookQue();

	std::vector<uintptr_t> pCreatedHooksArray;
}

uintptr_t Hooking::GetDiscordModuleBase()
{
	static uintptr_t discordModuleBase = 0;

	if (!discordModuleBase)
		discordModuleBase = (uintptr_t)GetModuleHandleA("DiscordHook64.dll");

	return discordModuleBase;
}

uintptr_t Hooking::GetSceneAddress()
{
	static uintptr_t presentSceneAdress = 0;

	if (!presentSceneAdress)
		presentSceneAdress = PatternScan(GetDiscordModuleBase(), ("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B D9 41 8B F8"));

	return presentSceneAdress;
}

short Hooking::GetAsyncKeyState(const int vKey)
{
	static uintptr_t addrGetAsyncKeyState = NULL;

	if (!addrGetAsyncKeyState)
		addrGetAsyncKeyState = PatternScan(GetDiscordModuleBase(), ("40 53 48 83 EC 20 8B D9 FF 15 ? ? ? ?"));

	if (!addrGetAsyncKeyState)
		return false;

	using GetAsyncKeyState_t = short(__fastcall*)(int);
	auto fnGetAyncKeyState = (GetAsyncKeyState_t)addrGetAsyncKeyState;

	return (fnGetAyncKeyState, vKey);
}

// Wrapper
bool Hooking::InsertHook(uintptr_t pOriginal, uintptr_t pHookedFunction, uintptr_t pOriginalCall)
{
	bool bAlreadyCreated = false;
	for (auto _Hook : pCreatedHooksArray)
	{
		if (_Hook == pOriginal)
		{
			bAlreadyCreated = true;
			break;
		}
	}

	if (!bAlreadyCreated)
		bAlreadyCreated = CreateHook(pOriginal, pHookedFunction, pOriginalCall);

	if (bAlreadyCreated)
		if (EnableHook(pOriginal, true))
			if (EnableHookQue())
				return true;

	return false;
}

bool Hooking::RemoveHook(uintptr_t pOriginal)
{
	bool bAlreadyCreated = false;
	for (auto _Hook : pCreatedHooksArray)
	{
		if (_Hook == pOriginal)
		{
			bAlreadyCreated = true;
			break;
		}
	}

	if (bAlreadyCreated)
		if (EnableHook(pOriginal, false))
			if (EnableHookQue())
				return true;

	return false;
}

// Internal Calls
bool Hooking::CreateHook(uintptr_t pOriginal, uintptr_t pHookedFunction, uintptr_t pOriginalCall)
{
	static uintptr_t addrCreateHook = NULL;

	if (!addrCreateHook)
		addrCreateHook = PatternScan(GetDiscordModuleBase(), ("40 53 55 56 57 41 54 41 56 41 57 48 83 EC 60"));

	if (!addrCreateHook)
		return false;

	using CreateHook_t = uint64_t(__fastcall*)(LPVOID, LPVOID, LPVOID*);
	auto fnCreateHook = (CreateHook_t)addrCreateHook;

	return (fnCreateHook, (void*)pOriginal, (void*)pHookedFunction, (void**)pOriginalCall) == 0 ? true : false;
}

bool Hooking::EnableHook(uintptr_t pTarget, bool bIsEnabled)
{
	static uintptr_t addrEnableHook = NULL;

	if (!addrEnableHook)
		addrEnableHook = PatternScan(GetDiscordModuleBase(), ("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 33 F6 8B FA"));

	if (!addrEnableHook)
		return false;

	using EnableHook_t = uint64_t(__fastcall*)(LPVOID, bool);
	auto fnEnableHook = (EnableHook_t)addrEnableHook;

	return (fnEnableHook, (void*)pTarget, bIsEnabled) == 0 ? true : false;
}

GObjects* objects = nullptr;
bool Hooking::EnableHookQue()
{
	static uintptr_t addrEnableHookQueu = NULL;

	if (!addrEnableHookQueu)
		addrEnableHookQueu = PatternScan(GetDiscordModuleBase(), ("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 57"));

	if (!addrEnableHookQueu)
		return false;

	using EnableHookQueu_t = uint64_t(__stdcall*)(VOID);
	auto fnEnableHookQueu = (EnableHookQueu_t)addrEnableHookQueu;

	return (fnEnableHookQueu) == 0 ? true : false;
}
namespace HkScene {

	bool Hook()
	{
		const auto pcall_present_discord = PatternScan(Hooking::GetDiscordModuleBase(),
			skCrypt("FF 15 ? ? ? ? 8B D8 E8 ? ? ? ? E8 ? ? ? ? EB 10"));
		if (!pcall_present_discord)
			return FALSE;
		const auto poriginal_present = reinterpret_cast<f_present*>(pcall_present_discord +
			*reinterpret_cast<int32_t*>(pcall_present_discord + 0x2) + 0x6);
		if (!*poriginal_present)
			return FALSE;
		SwapChain = *poriginal_present;
		*poriginal_present = hk_present;
		auto presentSceneAdress = PatternScan(Hooking::GetDiscordModuleBase(),
			skCrypt("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B D9 41 8B F8"));
		Hooking::InsertHook(presentSceneAdress, (uintptr_t)hk_present, (uintptr_t)&PresentOriginal);
	}

}
namespace Hooks
{
	bool Initialize()
	{
		// Creates window to UE4 Game (Fortnite).
		HWND UE4HWND = FindWindowA(skCrypt("UnrealWindow"), skCrypt("Fortnite  "));
		if (!UE4HWND) UE4HWND = GetForegroundWindow();
		if (!UE4HWND) return false;

		GameWindow = UE4HWND;

		// Initializes the main hook of the cheat.
		uint64_t uworld_address = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"), skCrypt("48 89 05 ? ? ? ? 48 8B B6 ? ? ? ?"))); uworld_address = reinterpret_cast<uintptr_t>(RELATIVE_ADDR(uworld_address, 7));
		uint64_t uobject_address = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"), skCrypt("E8 ? ? ? ? 44 8B 4E 04 4C 8B C0"))); // possible sig: 48 8B 05 ? ? ? ? 4C 8D 34 CD

		uobject_address = reinterpret_cast<uintptr_t>(RELATIVE_ADDR(uobject_address, 7));
		
		data::OFFSET_UWORLD = uworld_address;
		data::OFFSET_UOBJECT = uobject_address;
		data::OFFSET_GETOBJECTNAMES = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"), skCrypt("40 53 48 83 EC 20 48 8B D9 48 85 D2 75 45 33 C0 48 89 01 48 89 41 08 8D 50 05 E8 ? ? ? ? 8B 53 08 8D 42 05 89 43 08 3B 43 0C 7E 08 48 8B CB E8 ? ? ? ? 48 8B 0B 48 8D 15 ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? 48 8B C3 48 83 C4 20 5B C3 48 8B 42 18")));
		data::OFFSET_GETNAMEBYINDEX = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"), skCrypt("48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 30 8B")));
		data::OFFSET_FNFREE = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"), skCrypt("48 85 C9 74 2E 53 48 83 EC 20 48 8B D9 48 8B 0D ? ? ? ? 48 85 C9 75 0C")));

		//getweaponstats pattern
		auto addr = Utilities::FindPattern(skCrypt("\x48\x83\xEC\x58\x48\x8B\x91\x00\x00\x00\x00\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\xF6\x81\x00\x00\x00\x00\x00\x74\x10\x48\x8B\x81\x00\x00\x00\x00\x48\x85\xC0\x0F\x85\x00\x00\x00\x00\x48\x8B\x8A\x00\x00\x00\x00\x48\x89\x5C\x24\x00\x48\x8D\x9A\x00\x00\x00\x00\x48\x85\xC9"), skCrypt("xxxxxxx????xxxxx????xx?????xxxxx????xxxxx????xxx????xxxx?xxx????xxx"));
		if (!addr) {
			return FALSE;
		}
		GetWeaponStats = reinterpret_cast<decltype(GetWeaponStats)>(addr);

		// Free
		addr = Utilities::FindPattern("\x48\x85\xC9\x74\x2E\x53\x48\x83\xEC\x20\x48\x8B\xD9\x48\x8B\x0D\x00\x00\x00\x00\x48\x85\xC9\x75\x0C", "xxxxxxxxxxxxxxxx????xxxxx");
		if (!addr) {
			//Warn("Free failed!");
			return FALSE;
		}
		FreeInternal = reinterpret_cast<decltype(FreeInternal)>(addr);

		GetObjectNameInternal = reinterpret_cast<decltype(GetObjectNameInternal)>(data::OFFSET_GETOBJECTNAMES);
		objects = reinterpret_cast<decltype(objects)>(data::OFFSET_UOBJECT);


		uint64_t ValidateFire_address = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"),
			skCrypt("E8 ? ? ? ? 0F B6 D8 EB 9E")));
		uintptr_t ValidateFire_add = (ValidateFire_address + *(DWORD*)(ValidateFire_address + 0x1) + 0x5 - 0x100000000);

		auto GetBounds_Addr = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"),
			skCrypt("E8 ? ? ? ? 48 8B 4D 77 B3 01")));
		Offsets::fnGetBounds = (GetBounds_Addr + *(DWORD*)(GetBounds_Addr + 0x1) + 0x5);

		auto GetBoneMatrix_add = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"),
			skCrypt("E8 ? ? ? ? 48 8B 47 30 F3 0F 10 45")));
		Offsets::fnGetBoneMatrix = (GetBoneMatrix_add + *(DWORD*)(GetBoneMatrix_add + 0x1) + 0x5 - 0x100000000);

		Offsets::fnLineOfSightTo = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"),
			skCrypt("40 55 53 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 E0 49")));

		Offsets::fnGetWeaponStats = (memory::occurence(skCrypt("FortniteClient-Win64-Shipping.exe"),
			skCrypt("48 83 EC 58 48 8B 91 ? ? ? ? 48 85 D2 0F 84 ? ? ? ? F6 81 ? ? ? ? ? 74 10 48 8B 81 ? ? ? ? 48 85 C0 0F 85 ? ? ? ? 48 8B 8A ? ? ? ? 48 89 5C 24 ? 48 8D 9A ? ? ? ? 48 85 C9")));
		if (!ValidateFire_add || !Offsets::fnGetBounds || !IsValid(Offsets::fnGetBoneMatrix) || !IsValid(Offsets::fnLineOfSightTo) || !IsValid(Offsets::fnGetWeaponStats)) { return 0; }

		// IAT Table Swap
		oWndProc = (WNDPROC)SetWindowLongPtrW(UE4HWND, GWLP_WNDPROC, (LONG_PTR)hkWndProc);

		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);

		//DWORD64 UWorld = p1337((DWORD64)GetModuleHandle(0), "48 89 05 ? ? ? ? 48 8B B6 ? ? ? ?");
		//std::cout << "UWorld 1: " << std::hex << UWorld << std::endl;
		//UWorld = (DWORD64)Utilities::FindPattern("\x48\x89\x05\x00\x00\x00\x00\x48\x8B\xB6\x00\x00\x00\x00", "xxx????xxx????");
		//std::cout << "UWorld: " << std::hex << GetModuleHandle(0) - UWorld << std::endl;
		//std::cout << "UWorld: " << std::hex << UWorld - (DWORD64)GetModuleHandle(0) << std::endl;
		//std::cout << "UWorld: " << std::hex << UWorld << std::endl;
		// Hook from Discord (dsc)
		HkScene::Hook();
		return true;
	}

	void Start()
	{
		if (!Hooks::Initialize()) { 
			MessageBox(0, skCrypt(L"dx11 context cannot be written via iat. err code: 12875"), 0, 0);
			return;
		}
		if (!InitGetKeys()) {
			MessageBox(0, skCrypt(L"dx11 context cannot be written via iat. err code: 12875"), 0, 0);
			return;
		}
	}
}