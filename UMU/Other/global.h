#pragma once
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include <fstream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <shellapi.h>
#include <stdint.h>


#include "../stdafx.h"

namespace Global
{
	static DWORD_PTR BaseAddress;
	static MODULEINFO info;
}
extern bool BingoBongo;
extern bool Initialized;
extern uintptr_t GBA;
extern std::string Timestamped;
extern std::string Timestamp;
extern std::wstring INI_Path;
extern std::wstring LOG_Path;
extern std::wstring Directory_Str;
extern std::string DLL0;
extern std::string DLL1;
extern std::string DLL2;
extern std::string DLL3;
extern std::string DLL4;
extern std::string DLL5;
extern std::string DLL6;
extern std::string DLL7;
extern std::string DLL8;
extern std::string DLL9;
extern std::string DLL10;
extern int Timer0;
extern int Timer1;
extern int Timer2;
extern int Timer3;
extern int Timer4;
extern int Timer5;
extern int Timer6;
extern int Timer7;
extern int Timer8;
extern int Timer9;
extern int Timer10;
extern bool Library0;
extern bool Library1;
extern bool Library2;
extern bool Library3;
extern bool Library4;
extern bool Library5;
extern bool Library6;
extern bool Library7;
extern bool Library8;
extern bool Library9;
extern bool Library10;

extern bool D0;
extern bool D1;
extern bool D2;
extern bool D3;
extern bool D4;
extern bool D5;
extern bool D6;
extern bool D7;
extern bool D8;
extern bool D9;
extern bool D10;

extern bool HookWarning;
extern bool BypassSE;
extern bool BypassIF;
extern std::wstring LoadedLibraries;
extern int Hourglass;
extern int LibraryCt;

extern std::wstring Convertion(const std::string& narrowStr);
extern std::string Revertion(const std::wstring& wideStr);

/*extern WCHAR EXEPath[MAX_PATH];
extern std::wstring DirectoryPath;
extern size_t EndDL;*/