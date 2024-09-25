#include "Clock.h"

namespace Clock_M {

	int* Calendar_Vars[] = { &Day, &Minute, &Year };
	int* Clock_Vars[] = { &Second, &Minute, &Hour };

	bool* Prefixes[] = { &Pre_Second, &Pre_Minute, &Pre_Hour, &Pre_Day, &Pre_Month };
	int* Clocks[] = { &Month, &Day, &Hour, &Minute, &Second };

	void InitCounter() {
		std::ofstream Log(COUNTER_Path);
		Log.close();
	}
	void CounterLogger(std::string Time) {
		std::ofstream Log(COUNTER_Path, std::ios::app);
		Log << Time;
	}

	bool Is_Leap_Year(int Year) {
		return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
	}

	// To-String (TS)
	std::string TS(const int& I) { 
		std::string TS = std::to_string(I);
		return TS;
	}

	std::string Prefix(int Value) {
		std::string ReturnValue = (*Clocks[Value] < 10 ? "0" : "");
		return ReturnValue;
	}

	// Of The Month
	int Last_Day(const int& Month) { 
		int Months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (Is_Leap_Year(Year)) {
			Months[1] = 29;
		}

		int For_Month = Months[Month];
		return For_Month;
	}

	void Reset_Int(int Power, bool Clock) {
		for (int i = 0; i < Power; ++i) {
			switch (Clock) {
			case true:
				*Clock_Vars[i] = 0;
				break;
			case false:
				*Calendar_Vars[i] = 1;
				break;
			}
		}
	}
	
	void Tick() {
		Sleep(1 * 1000);
	}

	void Update_Time() {
		const std::string S = "/";
		const std::string C = ":";

		G_Year = TS(Year);
		G_Month = Prefix(0) + TS(Month);
		G_Day = Prefix(1) + TS(Day);
		G_Hour = Prefix(2) + TS(Hour);
		G_Minute = Prefix(3) + TS(Minute);
		G_Second = Prefix(4) + TS(Second);

		Full_Date = G_Month + S + G_Day + S + G_Year + " " + G_Hour + C + G_Minute + C + G_Second + " " + Meridiem;
	}

	void InitClock() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
		std::tm now_tm;
		localtime_s(&now_tm, &now_time_t);

		Stream::Year << std::put_time(&now_tm, "%Y");
		Stream::Month << std::put_time(&now_tm, "%m");
		Stream::Day << std::put_time(&now_tm, "%d");

		Stream::Hour << std::put_time(&now_tm, "%H");
		Stream::Minute << std::put_time(&now_tm, "%M");
		Stream::Second << std::put_time(&now_tm, "%S");

		Year = std::stoi(Stream::Year.str());
		Month = std::stoi(Stream::Month.str());
		Day = std::stoi(Stream::Day.str());

		Hour = std::stoi(Stream::Hour.str());
		Minute = std::stoi(Stream::Minute.str());
		Second = std::stoi(Stream::Second.str());

		for (int i = 0; i < 5; ++i) {
			*Prefixes[i] = (*Clocks[i] < 10);
		}

		Meridiem = (Hour < 12 ? "AM" : "PM");

		Update_Time();

		CounterLogger("Creating Thread\n");
		HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Constant_Clock, nullptr, 0, 0);
		if (hThread != nullptr)
			CloseHandle(hThread);
	}


	void Constant_Clock() {
		if (!Live_Clock) {
			return;
		}

		if (!Separate_Values) {
			std::string G_Year;
			std::string G_Month;
			std::string G_Day;
			std::string G_Hour;
			std::string G_Minute;
			std::string G_Second;
		}

		while (true) {

			if (Second <= 58) {
				Second += 1;
				Tick();
			}
			else if (Second == 59 && Minute <= 58) {
				Minute += 1;	
				Reset_Int(1, true);
				Tick();
			}
			else if (Minute == 59) {
				if (Hour < 23) {
					Hour += 1;
					Reset_Int(2, true);
				}
				else {
					Reset_Int(3, true); 
					if (Day < Last_Day(Month)) {
						Day += 1;
					}
					else {
						Reset_Int(1, false);
						if (Month < 12) {
							Month += 1;
						}
						else {
							Reset_Int(2, false);
							Year += 1;
						}
					}
				}
				Tick();
			}

			for (int i = 0; i < 5; ++i) {
				*Prefixes[i] = (*Clocks[i] < 10);
			}

			Meridiem = (Hour < 12 ? "AM" : "PM");
			Update_Time();
			
			printf((Full_Date + "\n\n").c_str());
		}
	}
}



