#pragma once
#include "pch.h"

std::string OnOff( bool x )
{
	if ( x )
		return "ON ";
	else
		return "OFF";
}
std::string Attached( bool x )
{
	if ( x )
		return "ATTACHED";
	else
		return "DISCONNECTED";
}

void PrintMenu( bool bAmmo, bool bHealth, bool bArmor, bool bSpeed, bool bRecoil, bool bAttached )
{
	system( "cls" );

	std::cout
		<< "-------------------------------------------\n"
		<< "              Govix's Cheat              \n"
		<< "-------------------------------------------\n"
		<< "STATUS: " << Attached( bAttached ) << "\n"
		<< "[NUM1] Ammo:\t\t\t--> " << OnOff( bAmmo ) << " <--" << "\n"
		<< "[NUM2] Health:\t\t\t--> " << OnOff( bHealth ) << " <--" << "\n"
		<< "[NUM3] Armor:\t\t\t--> " << OnOff( bArmor ) << " <--" << "\n"
		<< "[NUM4] Speed:\t\t\t--> " << OnOff( bSpeed ) << " <--" << "\n"
		<< "[NUM5] Recoil:\t\t\t--> " << OnOff( bRecoil ) << " <--" << "\n"
		<< "[HOME] Exit\n"
		<< "-------------------------------------------\n";

}

void ShowConsoleCursor( bool showFlag ) // Borrowed from StackOverflow
{
	HANDLE out = GetStdHandle( STD_OUTPUT_HANDLE );

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo( out, &cursorInfo );
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo( out, &cursorInfo );
}