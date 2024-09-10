#include "Debugger.h"
#include "../Other/global.h"

std::string FullTime;
int Month;
int Day;
int Year;
int Prehour;
int Hour;
int Preminute;
int Minute;
int Presecond;
int Second;
std::string Meridiem;

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

void Real_Time_Clock() { // Theoretical function, not actually being used anywhere and isn't callable globally unless defined in the header.
	auto now = std::chrono::system_clock::now();
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
	std::tm now_tm;
	localtime_s(&now_tm, &now_time_t);
	std::stringstream Initialize;
	std::stringstream MonthSS;
	std::stringstream DaySS;
	std::stringstream YearSS;
	std::stringstream HourSS;
	std::stringstream MinuteSS;
	std::stringstream SecondSS;
	std::stringstream MeridiemSS;

	MonthSS << std::put_time(&now_tm, "%m");
	
	DaySS << std::put_time(&now_tm, "%d");
	
	YearSS << std::put_time(&now_tm, "%Y");
	
	HourSS << std::put_time(&now_tm, "%H");
	
	MinuteSS << std::put_time(&now_tm, "%M");
	
	SecondSS << std::put_time(&now_tm, "%S");
	
	MeridiemSS << std::put_time(&now_tm, "%p");
	

	FullTime = MonthSS.str() + "/" + DaySS.str() + "/" + YearSS.str() + " " + HourSS.str() + ":" + MinuteSS.str() + ":" + SecondSS.str() + " " + MeridiemSS.str();

	Month = std::stoi(MonthSS.str());
	Day = std::stoi(DaySS.str());
	Year = std::stoi(YearSS.str());
	Hour = std::stoi(HourSS.str());
	if (Hour <= 10) {
		Prehour = 0;
	}
	Minute = std::stoi(MinuteSS.str());
	if (Minute <= 10) {
		Preminute = 0;
	}
	Second = std::stoi(SecondSS.str());
	if (Second <= 10) {
		Presecond = 0;
	}
	//Meridiem = MeridiemSS.str();
	if (Hour <= 12) {
		Meridiem = "AM";
	}
	else {
		Meridiem = "PM";
	}
	

	while (true) {
		if (Second <= 59) {
			if (Second <= 9) {
				Presecond = 0;
			}
			else {
				Presecond = 1;
			}
			Second += 1;
			Sleep(1 * 1000);
		}
		else if (Second == 60 && Minute <= 58) {
			if (Minute <= 9) {
				Preminute = 0;
			}
			else {
				Preminute = 1;
			}
			Minute += 1;
			Second = 0;
			Presecond = 0;
			Sleep(1 * 1000);
		}
		else if (Minute == 59) {
			if (Hour <= 9) {
				Prehour = 0;
			}
			else {
				Prehour = 1;
			}
			Minute = 0;
			Preminute = 0;
			if (Hour < 24) {
				Hour += 1;
			}
			else if (Hour == 24) {
				Prehour = 0;
				Hour = 0;
				Second = 0;
				Presecond = 0;
			}
			Sleep(1 * 1000);
		}
		if (Hour <= 12) {
			Meridiem = "AM";
		}
		else {
			Meridiem = "PM";
		}
	


		
	}
}

void InitCounter(const std::wstring& Path) {

}


void InitLog(const std::wstring& Path) {
	std::ofstream Log(Path);
	Log << "[" + RetrieveTime() + "] " << "[INITIALIZED] - UE4 Librarian has been successfully attached.\n";
	//Log << FullTime + "\n";
	Log.close();
}

void DebugLog(std::string LogType, std::string Text) {
	std::string Category = "[" + LogType + "] - ";
	std::ofstream Log(LOG_Path, std::ios::app);
	Log << "[" + RetrieveTime() + "] " << Category << Text + "\n";
}

void User_Exit(const std::string error) {
	DebugLog("EXIT", "Closing application due to user input.\REASON: " + error);
	// 'error' shows the name of the function that the MessageBox appeared in.
}