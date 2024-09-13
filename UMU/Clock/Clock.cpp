#include "../Clock/Clock.h"







namespace Clock_M {

	void InitCounter() {
		std::ofstream Log(COUNTER_Path);
		Log.close();
	}
	void CounterLogger(std::string Time) {
		std::ofstream Log(COUNTER_Path, std::ios::app);
		Log << Time;
	}

	bool Is_Leap_Year(int Year) {
		if ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0) {
			return true;
		}
		return false;
	}

	std::string TS(const int& I) { // To-String (TS)
		std::string TS = std::to_string(I);
		return TS;
	}

	std::string Prefix(const int Value) {
		bool Prefixes[] = { Pre_Second, Pre_Minute, Pre_Hour, Pre_Day, Pre_Month };
		std::string ReturnValue = (Value < 10 ? "0" : "");
		return ReturnValue;
	}

	int Last_Day(const int& Month) { // Of The Month
		int Months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (Is_Leap_Year(Year)) {
			Months[1] = 29;
		}

		int For_Month = Months[Month];
		return For_Month;
	}

	void Reset_Int(int Power, bool Clock) {
		int Power_Level[] = { Second, Minute, Hour};
		if (!Clock) {
			Power_Level[0] = Day;
			Power_Level[1] = Month;
			Power_Level[2] = Year;
		}
		for (int i = 0; i < (Power + 1); ++i) {
			Power_Level[i] = ((Clock) ? 0 : 1);
		}
	}
	
	void Tick() {
		Sleep(1 * 1000);
	}

	void InitClock() {
		InitCounter();
		//Sleep(10 * 1000);
		AllocConsole();
		FILE* f = new FILE();
		freopen_s(&f, "CONOUT$", "w", stdout);
		printf("\n\n\n\n\n\n\n\n\n\n\nHELLO EVERYBODY\n\n\n\n\n\n\n\n\n\n\n");

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

		bool Pre_Clocks[] = {Pre_Month, Pre_Day, Pre_Hour, Pre_Minute, Pre_Second };
		int Clocks[] = { Month, Day, Hour, Minute, Second };

		for (int i = 0; i < 4; ++i) {
			if (Clocks[i] < 10) {
				Pre_Clocks[i] = true;
				CounterLogger("Pre_Clocks[" + std::to_string(i) + "] = true;\n");
			}
		}
		Meridiem = (Hour < 12 ? "AM" : "PM");
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

		std::string S = "/";
		std::string C = ":";
		bool Pre_Clocks[] = { Pre_Month, Pre_Day, Pre_Hour, Pre_Minute, Pre_Second };
		int Clocks[] = { Month, Day, Hour, Minute, Second };

		while (true) {

			if (Second <= 58) {
				Second += 1;
				Tick();
			}
			else if (Second == 59 && Minute <= 58) {
				printf("else if (Second == 59 && Minute < 59) {\n");
				Minute += 1;	
				Reset_Int(0, true);
				Tick();
			}
			else if (Minute == 59) {
				printf("else if (Minute == 59) {\n");
				if (Hour < 23) {
					printf("if (Hour < 23) {\n");
					Hour += 1;
					Reset_Int(1, true);
				}
				else {
					Reset_Int(2, true); 
					if (Day < Last_Day(Month)) {
						printf("if (Day < Last_Day(Month)) {\n");
						Day += 1;
					}
					else {
						Reset_Int(0, false);
						if (Month < 12) {
							printf("if (Month > 12) {\n");
							Month += 1;
						}
						else {
							Reset_Int(1, false);
							Year += 1;
						}
					}
				}
				Tick();
			}

			for (int i = 0; i < 6; ++i) {
				if (Clocks[i] < 10) {
					Pre_Clocks[i] = true;
				}
			}

			Meridiem = (Hour < 12 ? "AM" : "PM");

			G_Year = TS(Year);
			G_Month = Prefix(4) + TS(Month);
			G_Day = Prefix(3) + TS(Day);
			G_Hour = Prefix(2) + TS(Hour);
			G_Minute = Prefix(1) + TS(Minute);
			G_Second = Prefix(0) + TS(Second);

			Full_Date = G_Month + S + G_Day + S + G_Year + " " + G_Hour + C + G_Minute + C + G_Second + " " + Meridiem;

			printf((Full_Date + "\n\n").c_str());
		}
	}
}



/*
void Real_Time_Clock() { // Theoretical function, not actually being used anywhere and isn't callable globally unless defined in the header.
	Sleep(10 * 1000);
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
	if (Hour < 9) {
		Prehour = 0;
	}
	else {
		Prehour = 1;
	}
	Minute = std::stoi(MinuteSS.str());
	if (Minute < 9) {
		Preminute = 0;
	}
	else {
		Preminute = 1;
	}
	Second = std::stoi(SecondSS.str());
	if (Second < 9) {
		Presecond = 0;
	}
	else {
		Presecond = 1;
	}
	//Meridiem = MeridiemSS.str();
	if (Hour <= 12) {
		Meridiem = "AM";
	}
	else {
		Meridiem = "PM";
	}


	AllocConsole();
	FILE* f = new FILE();
	freopen_s(&f, "CONOUT$", "w", stdout);
	printf("\n\n\n\n\n\n\n\n\n\n\HELLO EVERYBODY\n\n\n\n\n\n\n\n\n\n\n");


	while (true) {
		if (Second <= 58) {
			if (Second < 9) {
				Presecond = 0;
			}
			else {
				Presecond = 1;
			}
			Second += 1;
			Sleep(1 * 1000);
		}
		else if (Second == 59 && Minute <= 58) {
			if (Minute < 9) {
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
			if (Hour < 9) {
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

		if (Presecond == 1) {
			FSecond = std::to_string(Second);
		}
		else {
			FSecond = std::to_string(Presecond) + std::to_string(Second);
		}
		if (Preminute == 1) {
			FMinute = std::to_string(Minute);
		}
		else {
			FMinute = std::to_string(Preminute) + std::to_string(Minute);
		}
		if (Prehour == 1) {
			FHour = std::to_string(Hour);
		}
		else {
			FHour = std::to_string(Prehour) + std::to_string(Hour);
		}

		FullTime = MonthSS.str() + "/" + DaySS.str() + "/" + YearSS.str() + " " + FHour + ":" + FMinute + ":" + FSecond + " " + Meridiem + "\n\n";

		//printf(FullTime.c_str());
		//CounterLogger(FullTime);
	}
}
*/