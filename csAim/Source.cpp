#include <Windows.h>
#include <iostream>
#include "Hack.h"

DWORD WINAPI OnDllAttach(PVOID base)
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("csAim - Counter-Strike: Global Offensive");
	std::cout << "Money in my right and my left hand, Ridin' on a horse with a dead man\n\n";
	std::cout << "Build: 16 July\n";
	std::cout << "Made by hj.#0010\n";
#endif

	while (!(GetAsyncKeyState(VK_DELETE) & 0x8000))
	{
		Run();
		Sleep(1);
	}
	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 0);
}

VOID WINAPI OnDllDetach()
{
#ifdef _DEBUG
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);

	HWND hw_ConsoleHwnd = GetConsoleWindow();
	FreeConsole();
	PostMessageW(hw_ConsoleHwnd, WM_CLOSE, 0, 0);
#endif
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)OnDllAttach, hModule, NULL, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{

		OnDllDetach();
	}
	return TRUE;
}