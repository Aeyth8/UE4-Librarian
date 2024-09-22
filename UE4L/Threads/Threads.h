#pragma once
#include "../global.h"
void Thread_Creator();
DWORD WINAPI LoadLibraries(int Lib);
void AttachDLL0();
void AttachDLL1();
void AttachDLL2();
void AttachDLL3();
void AttachDLL4();
void AttachDLL5();
void AttachDLL6();
void AttachDLL7();
void AttachDLL8();
void AttachDLL9();
void AttachDLL10();
void Attach_Failed(const std::wstring& DLLName);
