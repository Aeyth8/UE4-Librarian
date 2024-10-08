// DXGI Proxy Created By GHFear/Illusory/ASMRGaming

// UE4 Librarian Written By Aeyth8

#include "global.h"
#include "./Parsing/parsing.h"
#include "Proxy/proxy.h"


EXTERN_C IMAGE_DOS_HEADER __ImageBase; // Placeholder
HMODULE ourModule = 0; // Passed to proxy.cpp

/*

/////// Process Map For UE4-Librarian \\\\\\\

DLL Entry -> Initialize(); -> Parse_INI(); -> Thread_Creator(); -> 11 Threads [ AttachDLL0 - AttachDLL10 ]
dllmain.cpp  parsing.cpp      parsing.cpp    Threads.cpp          Threads.cpp

                  |               
				 \|/             
				  v               
			  InitLog();        
			  Debugger.cpp

*/


BOOL APIENTRY DllMain(HMODULE hModule, int ul_reason_for_call, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);
	Initialize();
	
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		ourModule = hModule;
		
		Proxy_Attach();

	}
	if (ul_reason_for_call == DLL_PROCESS_DETACH)
		Proxy_Detach();

	return TRUE;
}
