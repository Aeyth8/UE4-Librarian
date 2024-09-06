#pragma once
#include <string>

std::string RetrieveTime();
void InitLog(const std::wstring& Path);
void DebugLog(std::string LogType, std::string Text);