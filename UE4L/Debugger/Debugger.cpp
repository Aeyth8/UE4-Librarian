#include "Debugger.h"
#include "../global.h"
#include "../Clock/Clock_P.h"

std::string RetrieveTime() { // Retrieves the current time into a permanent stamp, then after initialized places the current time into a constantly changed variable.
	auto now = std::chrono::system_clock::now();
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
	std::tm now_tm;
	localtime_s(&now_tm, &now_time_t);

	if (!Initialized) {
		Initialized = true;
		std::stringstream Timestamped;
		Timestamped << std::put_time(&now_tm, "%m/%d/%Y %H:%M:%S %p");

		return Timestamped.str();
	}
	else {
		std::stringstream Timestamp;
		Timestamp << std::put_time(&now_tm, "%m/%d/%Y %H:%M:%S %p");

		return Timestamp.str();
	}
}

void InitLog(const std::wstring& Path) {
	std::ofstream Log(Path);
	Log << "[" + Full_Date + "] " << "[INITIALIZED] - UE4 Librarian has been successfully attached.\n";
	Log.close();
}

void DebugLog(std::string LogType, std::string Text) {
	std::string Category = "[" + LogType + "] - ";
	std::ofstream Log(LOG_Path, std::ios::app);
	Log << "[" + Full_Date + "] " << Category << Text + "\n";
}

void User_Exit(const std::string error) {
	DebugLog("EXIT", "Closing application due to user input. REASON: " + error);
	// 'error' shows the name of the function that the MessageBox appeared in.
}



/// REMINDER TO SELF:

// InitLog()
// Initialize()
// API Entry

// These contain all traces of experimental code being executed by runtime.

// ALSO MAKE SURE YOU ADD A FUNCTION TO CLOSE DEBUG LOG, IT MAY SEEM POINTLESS BUT IT MAY CRASH IF CLOSED AT THE EXACT MOMENT.

// ADD A INI OPTION FOR 24 HOUR TIME OR 12 HOUR.

// PS if you have a problem check to see IsValidDLL where you changed it to constants (Which to my understanding is correct but I could end up wrong)