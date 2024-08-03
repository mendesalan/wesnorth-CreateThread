#include <Windows.h>

void injected_thread() 
{
	MessageBox(0, L"Injected!", L"Success", 0);

	while (true) 
	{
		if (GetAsyncKeyState('M')) 
		{
			DWORD* player_base = (DWORD*)0x017EED18;
			DWORD* game_base = (DWORD*)(*player_base + 0xA90);
			DWORD* gold = (DWORD*)(*game_base + 4);
			*gold += 10;
		}
		Sleep(1);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) 
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL);
	}

	return true;
}