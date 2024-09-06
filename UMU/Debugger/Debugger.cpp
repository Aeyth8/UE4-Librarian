#include "Debugger.h"
#include "../stdafx.h"
#include <stdint.h>
#include <stdio.h>
#include <shellapi.h>
#include <iostream>
#include <algorithm>
#include "../Other/global.h"
#include "../DXGIProxy/proxy.h"
#include "fstream"
#include "string"
#include <chrono>

//bool Initialized = false;
//std::string Timestamped;

std::string RetrieveTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
	std::tm now_tm;
	localtime_s(&now_tm, &now_time_t);

	if (!Initialized) {
		Initialized = true;
		std::stringstream Timestamped;
		Timestamped << std::put_time(&now_tm, "%Y/%m/%d %H:%M:%S %p");

		return Timestamped.str();
	}
	else {
		std::stringstream Timestamp;
		Timestamp << std::put_time(&now_tm, "%Y/%m/%d %H:%M:%S %p");

		return Timestamp.str();
	}
}

void InitLog(const std::wstring& Path) {
	std::ofstream Log(Path);
	Log << "[" + RetrieveTime() + "] " << "[INITIALIZED] - UE4 Librarian has been successfully attached.\n";
	Log.close();
}

void DebugLog(std::string LogType, std::string Text) {
	std::string Category = "[" + LogType + "] - ";
	std::ofstream Log(LOG_Path, std::ios::app);
	Log << "[" + RetrieveTime() + "] " << Category << Text + "\n";
}