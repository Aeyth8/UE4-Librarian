/*


Code is no longer in use / no longer connected to codebase

But I spent a lot of time working on it, so I will be saving it for ole' timesakes.

//------> Threads.cpp

void DidAnyLibrariesLoad() { // Loops through 11 iterations comparing a couple of arrays, parsing a string message and adding it into the LoadedLibraries string.
	std::string DLLs[] = { DLL0, DLL1, DLL2, DLL3, DLL4, DLL5, DLL6, DLL7, DLL8, DLL9, DLL10 };
	int Timers[] = { Timer0, Timer1, Timer2, Timer3, Timer4, Timer5, Timer6, Timer7, Timer8, Timer9, Timer10 };
	bool Libraries[] = { Library0, Library1, Library2, Library3, Library4, Library5, Library6, Library7, Library8, Library9, Library10 };

	for (int i = 0; i < 11; ++i) { // Loops through 11 times, the variable 'i' is initially defined as 0, and through each loop gains 1.
		if (Libraries[i]) { // Checks the libraries array for the boolean using the number of 'i', for example if 'i = 5' then it would be seeing if (Global::Library5) is true.
			std::wstring LoadLib = Convertion(DLLs[i]) + L" | DLL" + std::to_wstring(i) + L" | Timer: " + std::to_wstring(Timers[i]) + L"s\n"; // Parses a wide string, calling Convertion to convert the DLLs string into a wide string based on 'i', then it adds a string for format and adds the Timers integer converted to a wide string.
			LoadedLibraries += LoadLib; // Adds the parsed wide string message to LoadedLibraries, which in itself is a string, this loop will add each message for however many DLLs are successfully loaded.
			LibraryCt += 1; // Adds 1 to LibraryCt which means Library Count.
		}
	}
}

//------> dllmain.cpp

//Show an error message and give the choice whether to start the game without hooking, close and retry, or even file a lawsui- I mean an issue request.
void Hook_Failure() {

	Sleep(Hourglass * 1000); // It waits as long as the highest timer value + an additional second to allow the boolean values to change.
	DidAnyLibrariesLoad(); // It checks to see if any additional DLLs managed to load anyways.

	std::wstring Message1 = L"'dxgi.dll' failed to hook the game, this is due to:\n\n1: You're not using a supported Unreal Engine (4.0-4.27.2)\n\n2: This game has Steam's DRM, try to bypass this using Steamless or Goldberg Emulator.\n(I personally use Steam-Auto-Cracker but I don't pirate much)\n\n3: nÑ£ç†®π∫∆œ≈∫˙√©¥Ωø√ç∂˙´¬åß∂ƒ¨ˆˇœ´∆†¨¥∫∂˙ø¬˙∂˚´µ±˙¢∂¨∑∆√¬\n\n";

	std::wstring OCD = L"this DLL has"; // OCD is a simple variable to decide whether or not multiple DLLs have been loaded and changes the message accordingly, and something my OCD bothered me to implement/fix.
	if (LibraryCt > 1) { // If there are more than 1 DLLs that have successfully loaded, the text output will change accordingly.
		OCD = L"these DLLs have";
	}

	std::wstring Message2 = L"\nHOWEVER, " + OCD + L" still been loaded into the game successfully:\n\n" + LoadedLibraries;
	std::wstring EndLine = L"\n\nClick YES to open the GitHub repository and file a lawsui- I mean file an issue request. \n\nClick NO if you want to play the game without the special 'Mod Unlocker' hook working. \n\nClick CANCEL to close the game.";

	std::wstring FullMessage = Message1 + EndLine; // Simple variable to decide how much information is output, if no DLLs successfully load then it will only output Message1.
	if (LibraryCt > 0) { // But if any DLLs successfully manage to load, then it will output Message2, which includes OCD, LoadedLibraries, and the message describing the current options you have.
		FullMessage = Message1 + Message2 + EndLine;
	}

	if (HookWarning) {
		const int result = MessageBox(NULL, FullMessage.c_str(), L"! Error !", MB_YESNOCANCEL | MB_SYSTEMMODAL);

		switch (result)
		{
		case IDYES:
			ShellExecute(0, 0, L"https://github.com/Aeyth8/UE4-Librarian/issues/new", 0, 0, SW_SHOW);
			break;
		case IDNO:
			break;
		case IDCANCEL:
			User_Exit("[Hook_Failure]");
			abort();
			break;
		}
	}
}

//------> parsing.cpp

//It attempts to read a .ini file within the binaries directory named "DList.ini", if it is unable to find this file, it creates one.
void Set_Vars(const std::wstring& Path) {
	std::ifstream infile(Path);
	if (!infile.good()) { // If the file is not found, it will create one.
		std::ofstream outfile(Path);
		outfile << "[GUI]\n";
		outfile << "DisplayHookWarning=True\n";
		outfile << "BypassSyntaxError=False\n";
		outfile << "BypassIntegrityFailure=False\n\n";
		outfile << "[DLL]\n";
		outfile << "DLL0=PutYourDLLHere.dll\n";
		outfile << "DLL1=PutYourDLLHere.dll\n";
		outfile << "DLL2=PutYourDLLHere.dll\n";
		outfile << "DLL3=PutYourDLLHere.dll\n";
		outfile << "DLL4=PutYourDLLHere.dll\n";
		outfile << "DLL5=PutYourDLLHere.dll\n";
		outfile << "DLL6=PutYourDLLHere.dll\n";
		outfile << "DLL7=PutYourDLLHere.dll\n";
		outfile << "DLL8=PutYourDLLHere.dll\n";
		outfile << "DLL9=PutYourDLLHere.dll\n";
		outfile << "DLL10=PutYourDLLHere.dll\n\n";
		outfile << "[Timer]\n";
		outfile << "Timer0=JustPutANumberInSeconds\n";
		outfile << "Timer1=JustPutANumberInSeconds\n";
		outfile << "Timer2=JustPutANumberInSeconds\n";
		outfile << "Timer3=JustPutANumberInSeconds\n";
		outfile << "Timer4=JustPutANumberInSeconds\n";
		outfile << "Timer5=JustPutANumberInSeconds\n";
		outfile << "Timer6=JustPutANumberInSeconds\n";
		outfile << "Timer7=JustPutANumberInSeconds\n";
		outfile << "Timer8=JustPutANumberInSeconds\n";
		outfile << "Timer9=JustPutANumberInSeconds\n";
		outfile << "Timer10=JustPutANumberInSeconds\n\n";
		outfile.close();
		const int result = MessageBox(NULL, L"'DList.ini' was not found in the binaries, one has been created.", L"Relaunch The Game", MB_OK | MB_SYSTEMMODAL);
		switch (result)
		{
		case IDOK:
			User_Exit("[Set_Vars] DList.ini not found, a new one has been constructed.");
			abort();
			break;
		}
	}
	else {
		std::string line;
		std::string currentSection;

		while (std::getline(infile, line)) {
			// Trim whitespace from both ends of the line
			line.erase(line.find_last_not_of(" \t") + 1);
			line.erase(0, line.find_first_not_of(" \t"));

			// Skip empty lines and comments
			if (line.empty() || line[0] == ';') {
				continue;
			}

			// Check if line is a section header
			if (line[0] == '[' && line.back() == ']') {
				currentSection = line.substr(1, line.size() - 2);
				continue;
			}

			// Find the position of the equal sign
			auto pos = line.find('=');
			if (pos == std::string::npos) {
				continue; // Invalid line format
			}

			// Extract key and value
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);

			if (currentSection == "GUI") {
				if (key == "DisplayHookWarning" && value == "False") {
					HookWarning = false;
				}
				if (key == "BypassSyntaxError" && value == "True") {
					BypassSE = true;
				}
				if (key == "BypassIntegrityFailure" && value == "True") {
					BypassIF = true;
				}
			}
			// This is both inefficient, boring, and psychological torture ; PS - At the time of writing this I have been up for almost 24 hours straight :(
			// I am replying to my past self a few weeks later, I think this is the most efficient version that I could come up with for this, atleast with my current understanding of C++, which is small.
			if (currentSection == "DLL") {
				if (key == "DLL0" && IsValidDLL(value, key)) {
					DLL0 = value;
					D0 = true;
				}
				if (key == "DLL1" && IsValidDLL(value, key)) {
					DLL1 = value;
					D1 = true;
				}
				if (key == "DLL2" && IsValidDLL(value, key)) {
					DLL2 = value;
					D2 = true;
				}
				if (key == "DLL3" && IsValidDLL(value, key)) {
					DLL3 = value;
					D3 = true;
				}
				if (key == "DLL4" && IsValidDLL(value, key)) {
					DLL4 = value;
					D4 = true;
				}
				if (key == "DLL5" && IsValidDLL(value, key)) {
					DLL5 = value;
					D5 = true;
				}
				if (key == "DLL6" && IsValidDLL(value, key)) {
					DLL6 = value;
					D6 = true;
				}
				if (key == "DLL7" && IsValidDLL(value, key)) {
					DLL7 = value;
					D7 = true;
				}
				if (key == "DLL8" && IsValidDLL(value, key)) {
					DLL8 = value;
					D8 = true;
				}
				if (key == "DLL9" && IsValidDLL(value, key)) {
					DLL9 = value;
					D9 = true;
				}
				if (key == "DLL10" && IsValidDLL(value, key)) {
					DLL10 = value;
					D10 = true;
				}
			}
			if (currentSection == "Timer") {
				if (key == "Timer0" && D0 && IsValidTimer(value, key)) {
					Timer0 = std::stoi(value);
				}
				if (key == "Timer1" && D1 && IsValidTimer(value, key)) {
					Timer1 = std::stoi(value);
				}
				if (key == "Timer2" && D2 && IsValidTimer(value, key)) {
					Timer2 = std::stoi(value);
				}
				if (key == "Timer3" && D3 && IsValidTimer(value, key)) {
					Timer3 = std::stoi(value);
				}
				if (key == "Timer4" && D4 && IsValidTimer(value, key)) {
					Timer4 = std::stoi(value);
				}
				if (key == "Timer5" && D5 && IsValidTimer(value, key)) {
					Timer5 = std::stoi(value);
				}
				if (key == "Timer6" && D6 && IsValidTimer(value, key)) {
					Timer6 = std::stoi(value);
				}
				if (key == "Timer7" && D7 && IsValidTimer(value, key)) {
					Timer7 = std::stoi(value);
				}
				if (key == "Timer8" && D8 && IsValidTimer(value, key)) {
					Timer8 = std::stoi(value);
				}
				if (key == "Timer9" && D9 && IsValidTimer(value, key)) {
					Timer9 = std::stoi(value);
				}
				if (key == "Timer10" && D10 && IsValidTimer(value, key)) {
					Timer10 = std::stoi(value);
				}


			}
		}
	}
	int Highest_Value = (std::max)({ Timer0, Timer1, Timer2, Timer3, Timer4, Timer5, Timer6, Timer7, Timer8, Timer9, Timer10 }); // Finds the highest value of all timers and adds it to Hourglass (which is equal to 1), this is used for hook failure.
	Hourglass += Highest_Value;
	Thread_Creator();
}

*/


