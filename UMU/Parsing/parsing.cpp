#include "parsing.h"
#include "../stdafx.h"
#include <stdint.h>
#include <stdio.h>
#include <shellapi.h>
#include <iostream>
#include <algorithm>
#include "../Other/global.h"
#include "../DXGIProxy/proxy.h"
#include "../Debugger/Debugger.h"
#include "fstream"
#include "string"



// Stands for White Screen Of Death (WSOD) 
void WSOD(std::string key, std::string value, int errortype) {
	std::wstring DLLNum = Convertion(key);
	std::wstring DLLName = Convertion(value);
	if (errortype == 0) {
		std::wstring ErrorMessage = DLLNum + L"=" + DLLName + L" has failed to parse, please make sure you used proper syntax.\n\nAn example of proper formatting would be: " + DLLNum + L"=ExampleDLL.dll\n\n\nIf you would like to continue without loading this DLL, click 'OK', otherwise click 'CANCEL' to close the game.";
		const int result = MessageBox(NULL, ErrorMessage.c_str(), L"! Improper Syntax !", MB_OKCANCEL | MB_SYSTEMMODAL);
		switch (result)
		{
		case IDOK:
			break;
		case IDCANCEL:
			abort();
			break;
		}
	}
	else if (errortype == 1) {
		const std::wstring ErrorMessage = DLLName + L" was not found within your binaries.\n\nPlease make sure that:\n\n 1: You placed it in the proper folder, which is found within\n 'YourGameName/YourGameName/Binaries/Win64'\n\n 2: You properly typed the name of the DLL.\n\n (If you do not want to use this DLL, please remove it from 'DList.ini')";
		const int result = MessageBox(NULL, ErrorMessage.c_str(), L"! File Integrity Failed !", MB_OK | MB_SYSTEMMODAL);
		switch (result)
		{
		case IDOK:
			abort();
			break;
		}
	}
}

bool IsValidDLL(const std::string& value, const std::string& key) {
	std::string DLL_Template_Name = "PutYourDLLHere.dll";
	std::string ProperExtension = "dll";
	WCHAR X64[MAX_PATH] = { 0 };
	auto File_Extension_Dot = value.rfind('.');

	if (value == DLL_Template_Name || value.empty() || std::all_of(value.begin(), value.end(), ::isspace)) {
		return false;
	}

	if (File_Extension_Dot == std::string::npos) {
		WSOD(key, value, 0);
		return false;
	}
	std::string Extracted_Extension = value.substr(File_Extension_Dot + 1);

	if (Extracted_Extension != ProperExtension) {
		if (!BypassSE) {
			WSOD(key, value, 0);
		}
		return false;
	}
	wcsncpy_s(X64, (Convertion(value)).c_str(), _countof(X64) - 1);

	if (GetFileAttributesW(X64) == INVALID_FILE_ATTRIBUTES) {
		if (!BypassIF) {
			WSOD(key, value, 1);
		}
		return false;
	}

	return true;
}

bool IsValidTimer(const std::string& value) {
	std::string Timer_Template_Name = "JustPutANumberInSeconds";
	int Testing = 0;

	if (value == Timer_Template_Name || value.empty() || std::all_of(value.begin(), value.end(), ::isspace)) {
		return false;
	}

	try {
		Testing = std::stoi(value);
	}

	catch (const std::exception& e) {
		return false;
	}

	return true;
}



void Initialize() {
	WCHAR EXEPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, EXEPath, MAX_PATH);

	std::wstring DirectoryPath(EXEPath);
	GBA = uintptr_t(GetModuleHandleW(NULL));
	size_t EndDL = DirectoryPath.find_last_of(L"\\/");


	if (EndDL != std::wstring::npos) {
		// Remove the filename part to get the directory path
		DirectoryPath = DirectoryPath.substr(0, EndDL + 1); // Keep the backslash
	}

	INI_Path = DirectoryPath + L"DList.ini";
	LOG_Path = DirectoryPath + L"UE4-Librarian.log";

	InitLog(LOG_Path);
	DebugLog("INFO", "The Global Base Address [GBA] is " + std::to_string(GBA) + "\n\n");
	Set_Vars(INI_Path);
	
	/*std::ifstream ini(INI_Path);
	std::ifstream log(LOG_Path);
	if (!ini.good()) {

	}
	if (!log.good()) {

	}*/

}

//It attempts to read a .ini file within the binaries directory named "DList.ini", if it is unable to find this file, it creates one.
void Set_Vars(const std::wstring& Path) {
	std::ifstream infile(Path);
	if (!infile.good()) { // If the file is not found, it will create one.
		std::ofstream outfile(Path);
		outfile << "[GUI]\n";
		outfile << "DisplayHookWarning=True\n";
		outfile << "BypassSyntaxError=False\n";
		outfile << "BypassIntegrityFailure=False\n\n";
		outfile << "[DLL]\n";
		outfile << "DLL0=PutYourDLLHere.dll\n";
		outfile << "DLL1=PutYourDLLHere.dll\n";
		outfile << "DLL2=PutYourDLLHere.dll\n";
		outfile << "DLL3=PutYourDLLHere.dll\n";
		outfile << "DLL4=PutYourDLLHere.dll\n";
		outfile << "DLL5=PutYourDLLHere.dll\n";
		outfile << "DLL6=PutYourDLLHere.dll\n";
		outfile << "DLL7=PutYourDLLHere.dll\n";
		outfile << "DLL8=PutYourDLLHere.dll\n";
		outfile << "DLL9=PutYourDLLHere.dll\n";
		outfile << "DLL10=PutYourDLLHere.dll\n\n";
		outfile << "[Timer]\n";
		outfile << "Timer0=JustPutANumberInSeconds\n";
		outfile << "Timer1=JustPutANumberInSeconds\n";
		outfile << "Timer2=JustPutANumberInSeconds\n";
		outfile << "Timer3=JustPutANumberInSeconds\n";
		outfile << "Timer4=JustPutANumberInSeconds\n";
		outfile << "Timer5=JustPutANumberInSeconds\n";
		outfile << "Timer6=JustPutANumberInSeconds\n";
		outfile << "Timer7=JustPutANumberInSeconds\n";
		outfile << "Timer8=JustPutANumberInSeconds\n";
		outfile << "Timer9=JustPutANumberInSeconds\n";
		outfile << "Timer10=JustPutANumberInSeconds\n\n";
		outfile.close();
		const int result = MessageBox(NULL, L"'DList.ini' was not found in the binaries, one has been created.", L"Relaunch The Game", MB_OK | MB_SYSTEMMODAL);
		switch (result)
		{
		case IDOK:
			abort();
			break;
		}
	}
	else {
		std::string line;
		std::string currentSection;

		while (std::getline(infile, line)) {
			// Trim whitespace from both ends of the line
			line.erase(line.find_last_not_of(" \t") + 1);
			line.erase(0, line.find_first_not_of(" \t"));

			// Skip empty lines and comments
			if (line.empty() || line[0] == ';') {
				continue;
			}

			// Check if line is a section header
			if (line[0] == '[' && line.back() == ']') {
				currentSection = line.substr(1, line.size() - 2);
				continue;
			}

			// Find the position of the equal sign
			auto pos = line.find('=');
			if (pos == std::string::npos) {
				continue; // Invalid line format
			}

			// Extract key and value
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);

			if (currentSection == "GUI") {
				if (key == "DisplayHookWarning" && value == "False") {
					HookWarning = false;
				}
				if (key == "BypassSyntaxError" && value == "True") {
					BypassSE = true;
				}
				if (key == "BypassIntegrityFailure" && value == "True") {
					BypassIF = true;
				}
			}
			// This is both inefficient, boring, and psychological torture ; PS - At the time of writing this I have been up for almost 24 hours straight :(
			if (currentSection == "DLL") {
				if (key == "DLL0" && IsValidDLL(value, key)) {
					DLL0 = value;
					D0 = true;
				}
				if (key == "DLL1" && IsValidDLL(value, key)) {
					DLL1 = value;
					D1 = true;
				}
				if (key == "DLL2" && IsValidDLL(value, key)) {
					DLL2 = value;
					D2 = true;
				}
				if (key == "DLL3" && IsValidDLL(value, key)) {
					DLL3 = value;
					D3 = true;
				}
				if (key == "DLL4" && IsValidDLL(value, key)) {
					DLL4 = value;
					D4 = true;
				}
				if (key == "DLL5" && IsValidDLL(value, key)) {
					DLL5 = value;
					D5 = true;
				}
				if (key == "DLL6" && IsValidDLL(value, key)) {
					DLL6 = value;
					D6 = true;
				}
				if (key == "DLL7" && IsValidDLL(value, key)) {
					DLL7 = value;
					D7 = true;
				}
				if (key == "DLL8" && IsValidDLL(value, key)) {
					DLL8 = value;
					D8 = true;
				}
				if (key == "DLL9" && IsValidDLL(value, key)) {
					DLL9 = value;
					D9 = true;
				}
				if (key == "DLL10" && IsValidDLL(value, key)) {
					DLL10 = value;
					D10 = true;
				}
			}
			if (currentSection == "Timer") {
				if (key == "Timer0" && D0 && IsValidTimer(value)) {
					Timer0 = std::stoi(value);
				}
				if (key == "Timer1" && D1 && IsValidTimer(value)) {
					Timer1 = std::stoi(value);
				}
				if (key == "Timer2" && D2 && IsValidTimer(value)) {
					Timer2 = std::stoi(value);
				}
				if (key == "Timer3" && D3 && IsValidTimer(value)) {
					Timer3 = std::stoi(value);
				}
				if (key == "Timer4" && D4 && IsValidTimer(value)) {
					Timer4 = std::stoi(value);
				}
				if (key == "Timer5" && D5 && IsValidTimer(value)) {
					Timer5 = std::stoi(value);
				}
				if (key == "Timer6" && D6 && IsValidTimer(value)) {
					Timer6 = std::stoi(value);
				}
				if (key == "Timer7" && D7 && IsValidTimer(value)) {
					Timer7 = std::stoi(value);
				}
				if (key == "Timer8" && D8 && IsValidTimer(value)) {
					Timer8 = std::stoi(value);
				}
				if (key == "Timer9" && D9 && IsValidTimer(value)) {
					Timer9 = std::stoi(value);
				}
				if (key == "Timer10" && D10 && IsValidTimer(value)) {
					Timer10 = std::stoi(value);
				}
			}
		}
	}
	int Highest_Value = (std::max)({ Timer0, Timer1, Timer2, Timer3, Timer4, Timer5, Timer6, Timer7, Timer8, Timer9, Timer10 });
	Hourglass += Highest_Value;
}



