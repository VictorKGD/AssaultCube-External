#include "pch.h"
#include "console.h"
#include "proc.h"

int main()
{
	HWND console = GetConsoleWindow(); // Borrowed from StackOverflow
	{
		RECT r;
		GetWindowRect( console, &r );
		MoveWindow( console, r.left, r.top, 378, 240, TRUE );

		ShowConsoleCursor( false );
	}
	
	bool bAmmo = 0, bHealth = 0, bArmor = 0, bSpeed = 0, bRecoil = 0, bAttached = 0;

	DWORD procId;
	if ( GetProcId( L"ac_client.exe", procId ) )
		bAttached = true;
	else
	{
		MessageBox( console, L"Error", L"Could not attach to process", NULL );
		exit( EXIT_FAILURE );
	}

	uintptr_t moduleBase = GetModuleBaseAddress( procId, L"ac_client.exe" );

	HANDLE hProcess;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS, NULL, procId );

	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x10f4f4;

	// Hack
	std::vector<unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };
	uintptr_t ammoAddress = FindDMAAddy( hProcess, dynamicPtrBaseAddr, ammoOffsets );
	int newAmmo = 999;

	std::vector<unsigned int> healthOffsets = { 0xF8 };
	uintptr_t healthAddress = FindDMAAddy( hProcess, dynamicPtrBaseAddr, healthOffsets );
	int newHealth = 999;

	std::vector<unsigned int> armorOffsets = { 0xFC };
	uintptr_t armorAddress = FindDMAAddy( hProcess, dynamicPtrBaseAddr, armorOffsets );
	int newArmor = 999;

	std::vector<unsigned int> speedOffsets = { 0x80 };
	uintptr_t speedAddress = FindDMAAddy( hProcess, dynamicPtrBaseAddr, speedOffsets );
	int newSpeed = 10;
	int oldSpeed = 1;

	PrintMenu( bAmmo, bHealth, bArmor, bSpeed, bRecoil, bAttached );

	while ( !GetAsyncKeyState( VK_HOME ) )
	{
		if ( GetAsyncKeyState( VK_NUMPAD1 ) )
		{
			bAmmo = !bAmmo;

			PrintMenu( bAmmo, bHealth, bArmor, bSpeed, bRecoil, bAttached );
		}

		if ( GetAsyncKeyState( VK_NUMPAD2 ) )
		{
			bHealth = !bHealth;

			PrintMenu( bAmmo, bHealth, bArmor, bSpeed, bRecoil, bAttached );
		}

		if ( GetAsyncKeyState( VK_NUMPAD3 ) )
		{
			bArmor = !bArmor;

			PrintMenu( bAmmo, bHealth, bArmor, bSpeed, bRecoil, bAttached );
		}

		if ( GetAsyncKeyState( VK_NUMPAD4 ) )
		{
			bSpeed = !bSpeed;

			if (bSpeed) {
				WriteProcessMemory( hProcess, (BYTE*)speedAddress, &newSpeed, sizeof( newSpeed ), nullptr );
			}

			if (!bSpeed) {
				WriteProcessMemory( hProcess, (BYTE*)speedAddress, &oldSpeed, sizeof( oldSpeed ), nullptr );
			}

			PrintMenu( bAmmo, bHealth, bArmor, bSpeed, bRecoil, bAttached );
		}

		if ( GetAsyncKeyState( VK_NUMPAD5 ) )
		{
			bRecoil = !bRecoil;

			if (bRecoil) {
				NopEx( (BYTE*)( moduleBase + 0x63786 ), 10, hProcess );
			}
			else
			{
				PatchEx( (BYTE*)( moduleBase + 0x63786 ), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10, hProcess );
			}

			PrintMenu( bAmmo, bHealth, bArmor, bSpeed, bRecoil, bAttached );
		}

		{
			if (bHealth) {
				WriteProcessMemory( hProcess, (BYTE*)healthAddress, &newHealth, sizeof( newHealth ), nullptr );
			}

			if (bAmmo) {
				WriteProcessMemory( hProcess, (BYTE*)ammoAddress, &newAmmo, sizeof( newAmmo ), nullptr );
			}

			if (bArmor) {
				WriteProcessMemory( hProcess, (BYTE*)armorAddress, &newArmor, sizeof( newArmor ), nullptr );
			}
		}

		Sleep( 150 );
	}

	exit( EXIT_SUCCESS );
}