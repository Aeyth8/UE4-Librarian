#include "Threads.h"
#include "../global.h"
#include "../Debugger/Debugger.h"

typedef void(WINAPI* StartThread)();
HMODULE Bonkers = NULL;
WCHAR DLLPath[MAX_PATH] = { 0 };

const std::wstring Failed = L" has failed to load:\n\n\n Press 'OK' to play the game without this DLL.\n\n Press 'CANCEL' to close the game.";

void Thread_Creator() {
	for (int i = 0; i < 11; ++i) {

		if (*Ds[i]) {
			DebugLog(DLL_Keys[i], "Creating thread for " + *DLL_Vars[i] + " | Timer: " + std::to_string(*Timer_Vars[i]) + "s");
			LoadLibraries(i);
		}
		else {
			DebugLog("DLL" + std::to_string(i), "Skipping thread creation for " + *DLL_Vars[i] + " | Timer: " + std::to_string(*Timer_Vars[i]) + "s");
		}
	}
}



DWORD WINAPI LoadLibraries(int Lib) {
	StartThread Threads[] = { AttachDLL0, AttachDLL1, AttachDLL2, AttachDLL3, AttachDLL4, AttachDLL5, AttachDLL6, AttachDLL7, AttachDLL8, AttachDLL9, AttachDLL10 };

	if (!(Lib >= 0 && Lib <= 10)) {
		return 1;
	}

	HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Threads[Lib], nullptr, 0, 0);
	if (hThread != nullptr)
		CloseHandle(hThread);
	// Haven't found the cause of my screwup yet, but the log is timestamped 2 seconds after the actual timer, I'm not sure if this means the actual injection is inaccurate or if it's just the log.
	
	return 0;
}

// These are all separate threads to ensure that they are all properly timed and only work within themselves without affecting the other threads
void AttachDLL0() {
	std::wstring DLLName = Convertion(DLL0); //Converts the DLLName from a normal string to a wide string using the 'Convertion' function
	Sleep(Timer0 * 1000); // Sleeps for the amount of seconds you set in the timer via DList.ini, if you didn't set a timer then it will not sleep at all and will inject immediately, which is likely to cause a crash or fail entirely. Don't set a timer at 0, I'd recommend 4 seconds minimum.
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1); // Something something appends DLLName to the path
	Bonkers = LoadLibraryW(DLLPath); // Bonkers is a bool, and it will attempt to load the library (inject the custom DLL)
	if (!Bonkers) { // If the Bonkers bool ends up returning false, then it runs this error code, which pops up giving you the choice to continue without the DLL or to close the game.
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library0 = true;
		DebugLog("DLL0", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL1() {
	std::wstring DLLName = Convertion(DLL1);
	Sleep(Timer1 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library1 = true;
		DebugLog("DLL1", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL2() {
	std::wstring DLLName = Convertion(DLL2);
	Sleep(Timer2 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library2 = true;
		DebugLog("DLL2", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL3() {
	std::wstring DLLName = Convertion(DLL3);
	Sleep(Timer3 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library3 = true;
		DebugLog("DLL3", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL4() {
	std::wstring DLLName = Convertion(DLL4);
	Sleep(Timer4 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library4 = true;
		DebugLog("DLL4", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL5() {
	std::wstring DLLName = Convertion(DLL5);
	Sleep(Timer5 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library5 = true;
		DebugLog("DLL5", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL6() {
	std::wstring DLLName = Convertion(DLL6);
	Sleep(Timer6 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library6 = true;
		DebugLog("DLL6", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL7() {
	std::wstring DLLName = Convertion(DLL7);
	Sleep(Timer7 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library7 = true;
		DebugLog("DLL7", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL8() {
	std::wstring DLLName = Convertion(DLL8);
	Sleep(Timer8 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library8 = true;
		DebugLog("DLL8", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL9() {
	std::wstring DLLName = Convertion(DLL9);
	Sleep(Timer9 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library9 = true;
		DebugLog("DLL9", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void AttachDLL10() {
	std::wstring DLLName = Convertion(DLL10);
	Sleep(Timer10 * 1000);
	wcsncpy_s(DLLPath, DLLName.c_str(), _countof(DLLPath) - 1);
	Bonkers = LoadLibraryW(DLLPath);
	if (!Bonkers) {
		Attach_Failed(DLLName);
	}
	if (Bonkers) {
		Library10 = true;
		DebugLog("DLL10", Revertion(DLLName) + " has successfully loaded into the process.");
	}
}

void Attach_Failed(const std::wstring& DLLName) {
	std::wstring DoubleTime = L"'" + DLLName + L"'" + Failed;
	const int result = MessageBox(NULL, DoubleTime.c_str(), L"! ERROR !", MB_OKCANCEL | MB_SYSTEMMODAL);
	switch (result)
	{
	case IDOK:
		break;
	case IDCANCEL:
		User_Exit("[Attach_Failed] " + Revertion(DLLName));
		abort();
		break;
	}
}
