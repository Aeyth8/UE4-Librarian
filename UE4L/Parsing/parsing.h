#pragma once
#include <Windows.h>
#include <string>
#include <Psapi.h>


void WSOD(std::string key, std::string value, int errortype);
bool IsValidDLL(const std::string& value, const std::string& key);
bool IsValidTimer(const std::string& value, const std::string& key);
void Initialize();
void Parse_INI(const std::wstring& Path);
void Create_INI(const std::wstring& Path);


