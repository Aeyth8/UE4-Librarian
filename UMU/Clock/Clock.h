#pragma once
#include "../Other/global.h"

namespace Stream
{
	std::stringstream Year;
	std::stringstream Month;
	std::stringstream Day;

	std::stringstream Hour;
	std::stringstream Minute;
	std::stringstream Second;
};
namespace Clock_M//anipulation
{
	bool Is_Leap_Year(int Year);
	std::string TS(const int& I);
	std::string Prefix(const int Value);
	int Last_Day(const int& Month);
	void Reset_Int(int Power, bool Clock);
	void Tick();
	void InitClock();
	void Constant_Clock();
	

	int Year;
	int Month;
	int Day;

	int Hour;
	int Minute;
	int Second;
	std::string Meridiem;

	bool Pre_Hour;
	bool Pre_Minute;
	bool Pre_Second;
	bool Pre_Month;
	bool Pre_Day;
};
