#include "parsing.h"
#include "../global.h"
#include "../Proxy/proxy.h"
#include "../Debugger/Debugger.h"
#include "../Threads/Threads.h"



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
			User_Exit("[WSOD] (errortype == 0) / " + Revertion(DLLNum) + "=" + Revertion(DLLName));
			abort();
			break;
		}
	}
	else if (errortype == 1) {
		const std::wstring ErrorMessage = DLLName + L" was not found within your binaries.\n\nPlease make sure that:\n\n 1: You placed it in the proper folder, which is found within\n " + Directory_Str + DLLName + L"\n\n 2: You properly typed the name of the DLL.\n\n (If you do not want to use this DLL, please remove it from 'DList.ini')";
		const int result = MessageBox(NULL, ErrorMessage.c_str(), L"! File Integrity Failed !", MB_OK | MB_SYSTEMMODAL);
		switch (result)
		{
		case IDOK:
			User_Exit("[WSOD] (errortype 1) / " + Revertion(DLLName));
			abort();
			break;
		}
	}
}

bool IsValidDLL(const std::string& value, const std::string& key) {
	const std::string DLL_Template_Name = "PutYourDLLHere.dll";
	const std::string ProperExtension = "dll";
	std::wstring X64 = Directory_Str + Convertion(value);
	auto File_Extension_Dot = value.rfind('.');

	if (value == DLL_Template_Name || value.empty() || std::all_of(value.begin(), value.end(), ::isspace)) {
		DebugLog("IsValidDLL", key + " | FALSE | Error Type: EMPTY");
		return false;
	}

	if (File_Extension_Dot == std::string::npos) {
		DebugLog("IsValidDLL", key + " | FALSE | Error Type: MISSING EXTENSION");
		if (!BypassSE) {
			WSOD(key, value, 0);
		}
		return false;
	}
	std::string Extracted_Extension = value.substr(File_Extension_Dot + 1);

	if (Extracted_Extension != ProperExtension) {
		DebugLog("IsValidDLL", key + " | FALSE | Error Type: INVALID EXTENSION");
		if (!BypassSE) {
			WSOD(key, value, 0);
		}
		return false;
	}

	if (GetFileAttributesW(X64.c_str()) == INVALID_FILE_ATTRIBUTES) {
		DebugLog("IsValidDLL", key + " | FALSE | Error Type: INVALID_FILE_ATTRIBUTES / NOT FOUND");
		if (!BypassIF) {
			WSOD(key, value, 1);
		}
		return false;
	}

	DebugLog("IsValidDLL", key + " | VALID | " + value);
	return true;
}

bool IsValidTimer(const std::string& value, const std::string& key) {
	const std::string Timer_Template_Name = "JustPutANumberInSeconds";
	int Testing = 0;

	if (value == Timer_Template_Name || value.empty() || std::all_of(value.begin(), value.end(), ::isspace)) {
		DebugLog("IsValidTimer", key + " | FALSE | Error Type: EMPTY");
		return false;
	}

	try {
		Testing = std::stoi(value);
	}

	catch (const std::exception) {
		DebugLog("IsValidTimer", key + " | FALSE | Error Type: FAILED STRING CONVERTION");
		return false;
	}

	DebugLog("IsValidTimer", key + " | VALID | " + std::to_string(Testing) + "s");
	return true;
}



void Initialize() {
	WCHAR EXEPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, EXEPath, MAX_PATH);

	std::wstring DirectoryPath(EXEPath);
	size_t EndDL = DirectoryPath.find_last_of(L"\\/");
	std::wstring ShippingEXE;

	if (EndDL != std::wstring::npos) {
		// Remove the filename part to get the directory path
		DirectoryPath = DirectoryPath.substr(0, EndDL + 1); // Keep the backslash
		ShippingEXE = EXEPath + EndDL + 1;
	}

	GBA = uintptr_t(GetModuleHandleW(ShippingEXE.c_str()));
	INI_Path = DirectoryPath + L"DList.ini";
	LOG_Path = DirectoryPath + L"UE4-Librarian.log";
	COUNTER_Path = DirectoryPath + L"CountdownTester.log";
	Directory_Str = DirectoryPath;

	InitLog(LOG_Path);
	DebugLog("INFO", Revertion(ShippingEXE));
	DebugLog("INFO", "The Global Base Address [GBA] is " + std::to_string(GBA));
	Parse_INI(INI_Path);
}




void Parse_INI(const std::wstring& Path) {
	std::ifstream INI(Path);
	if (!INI.good()) {
		Create_INI(Path);
		return;
	}

	std::string line;
	std::string section;
	int DLL_Index = 0;
	int Timer_Index = 0;

	while (std::getline(INI, line)) {
		// Trim whitespace from both ends of the line
		line.erase(line.find_last_not_of(" \t") + 1);
		line.erase(0, line.find_first_not_of(" \t"));

		// Skip empty lines and comments
		if (line.empty() || line[0] == ';') {
			continue;
		}

		// Check if line is a section header
		if (line[0] == '[' && line.back() == ']') {
			section = line.substr(1, line.size() - 2);
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
	
		
		
		if (section == "GUI") {
			BypassSE = (key == "BypassSyntaxError" && value == "True");
			BypassIF = (key == "BypassIntegrityFailure" && value == "True");
		}
		if (section == "DLL" && DLL_Index < 11) {
			if (key == DLL_Keys[DLL_Index] && IsValidDLL(value, key)) {
				*DLL_Vars[DLL_Index] = value;
				*Ds[DLL_Index] = true;
			}
			DLL_Index += 1;
		}
		if (section == "Timer" && Timer_Index < 11) {
			if (key == Timer_Keys[Timer_Index] && *Ds[Timer_Index] && IsValidTimer(value, key)) {
				*Timer_Vars[Timer_Index] = std::stoi(value);
			}
			Timer_Index += 1;
		}
	}
	Thread_Creator();
}

void Create_INI(const std::wstring& Path) {
	std::ofstream INI(Path);
	INI << "[GUI]\nBypassSyntaxError=False\nBypassIntegrityFailure=False\n\n[DLL]\nDLL0=PutYourDLLHere.dll\nDLL1=PutYourDLLHere.dll\nDLL2=PutYourDLLHere.dll\nDLL3=PutYourDLLHere.dll\nDLL4=PutYourDLLHere.dll\nDLL5=PutYourDLLHere.dll\nDLL6=PutYourDLLHere.dll\nDLL7=PutYourDLLHere.dll\nDLL8=PutYourDLLHere.dll\nDLL9=PutYourDLLHere.dll\nDLL10=PutYourDLLHere.dll\n\n[Timer]\nTimer0=JustPutANumberInSeconds\nTimer1=JustPutANumberInSeconds\nTimer2=JustPutANumberInSeconds\nTimer3=JustPutANumberInSeconds\nTimer4=JustPutANumberInSeconds\nTimer5=JustPutANumberInSeconds\nTimer6=JustPutANumberInSeconds\nTimer7=JustPutANumberInSeconds\nTimer8=JustPutANumberInSeconds\nTimer9=JustPutANumberInSeconds\nTimer10=JustPutANumberInSeconds\n\n";
	INI.close();
	const int result = MessageBox(NULL, L"'DList.ini' was not found in the binaries, one has been created.", L"Relaunch The Game", MB_OK | MB_SYSTEMMODAL);
	switch (result)
	{
	case IDOK:
		User_Exit("[Set_Vars] DList.ini not found, a new one has been constructed.");
		abort();
		break;
	}
}