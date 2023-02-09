#pragma once
#include "pch.h"

bool GetProcId( const wchar_t* procName, DWORD& procId );

uintptr_t GetModuleBaseAddress( DWORD procId, const wchar_t* modName );

uintptr_t FindDMAAddy( HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets );

void PatchEx( BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess );

void NopEx( BYTE* dst, unsigned int size, HANDLE hProcess );