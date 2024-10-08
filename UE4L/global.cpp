#include "global.h"


// Debugging Variables ------>
bool Initialized = false;
bool Log_Unreal = true;
uintptr_t GBA = 0; // Global Base Address (GBA)
std::string Timestamped; // Timestamp set immediately during DLL entry
std::string Timestamp; // Timestamp sets each time a message in the debug log has been sent
std::wstring ShippingEXE;
std::wstring INI_Path;
std::wstring LOG_Path;
std::wstring CONSOLE_Path;
std::wstring Directory_Str;

//Set 11 Global Strings for DLLs simply because I don't know the easier way and I'm too tired ------>
std::string DLL0 = "Null";
std::string DLL1 = "Null";
std::string DLL2 = "Null";
std::string DLL3 = "Null";
std::string DLL4 = "Null";
std::string DLL5 = "Null";
std::string DLL6 = "Null";
std::string DLL7 = "Null";
std::string DLL8 = "Null";
std::string DLL9 = "Null";
std::string DLL10 = "Null";

// Set 11 Global Ints for timers ALSO ------>
int Timer0 = 4; // By default the timers are 4 seconds, this is because the DLL runs BY LAUNCH, meaning that any DLL attempting to load itself by launch is just going to fail, 4 seconds is the sweet spot.
int Timer1 = 4;
int Timer2 = 4;
int Timer3 = 4;
int Timer4 = 4;
int Timer5 = 4;
int Timer6 = 4;
int Timer7 = 4;
int Timer8 = 4;
int Timer9 = 4;
int Timer10 = 4;

// Set 11 Global Booleans for if they were successfully loaded ------>
bool Library0 = false;
bool Library1 = false;
bool Library2 = false;
bool Library3 = false;
bool Library4 = false;
bool Library5 = false;
bool Library6 = false;
bool Library7 = false;
bool Library8 = false;
bool Library9 = false;
bool Library10 = false;

// Set 11 Global Booleans that indicate whether a DLL is valid or not
bool D0 = false;
bool D1 = false;
bool D2 = false;
bool D3 = false;
bool D4 = false;
bool D5 = false;
bool D6 = false;
bool D7 = false;
bool D8 = false;
bool D9 = false;
bool D10 = false;

// Parsing Vars
bool BypassSE = false;
bool BypassIF = false;

// Converts a normal string into a wide string
std::wstring Convertion(const std::string& narrowStr) {
    std::wstring DLLName;
    DLLName.assign(narrowStr.begin(), narrowStr.end());
    return DLLName;
}

// Converts a wide string into a normal string
std::string Revertion(const std::wstring& wideStr) {
    std::string WideString;
    WideString.assign(wideStr.begin(), wideStr.end());
    return WideString;
}

//// ------> Essential Arrays (
std::string* DLL_Vars[] = { &DLL0, &DLL1, &DLL2, &DLL3, &DLL4, &DLL5, &DLL6, &DLL7, &DLL8, &DLL9, &DLL10 };
std::string DLL_Keys[] = { "DLL0", "DLL1", "DLL2", "DLL3", "DLL4", "DLL5", "DLL6", "DLL7", "DLL8", "DLL9", "DLL10" };

int* Timer_Vars[] = { &Timer0, &Timer1, &Timer2, &Timer3, &Timer4, &Timer5, &Timer6, &Timer7, &Timer8, &Timer9, &Timer10 };
std::string Timer_Keys[] = { "Timer0", "Timer1", "Timer2", "Timer3", "Timer4", "Timer5", "Timer6", "Timer7", "Timer8", "Timer9", "Timer10" };

bool* Ds[] = { &D0, &D1, &D2, &D3, &D4, &D5, &D6, &D7, &D8, &D9, &D10 };
//// <------ Essential Arrays )
