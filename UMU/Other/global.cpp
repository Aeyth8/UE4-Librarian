#include "Global.h"

namespace Global
{
    //Set an extremely important Global Boolean with a stupid name ------>
    bool BingoBongo = false;
    //Set 11 Global Strings for DLLs simply because I don't know the easier way and I'm too tired ------>
    std::string DLL0 = "Null";
    std::string DLL1 = "Null";
    std::string DLL2 = "Null";
    std::string DLL3 = "Null";
    std::string DLL4 = "Null";
    std::string DLL5 = "Null";
    std::string DLL6 = "Null";
    std::string DLL7 = "Null";
    std::string DLL8 = "Null";
    std::string DLL9 = "Null";
    std::string DLL10 = "Null";
    //Set 11 Global Ints for timers ALSO ------>
    int Timer0 = 4; // By default the timers are 4 seconds, this is because the DLL runs BY LAUNCH, meaning that any DLL attempting to load itself by launch is just going to fail, 4 seconds is the sweet spot.
    int Timer1 = 4;
    int Timer2 = 4;
    int Timer3 = 4;
    int Timer4 = 4;
    int Timer5 = 4;
    int Timer6 = 4;
    int Timer7 = 4;
    int Timer8 = 4;
    int Timer9 = 4;
    int Timer10 = 4;
    //Set 11 Global Booleans for if they were successfully loaded ------>
    bool Library0 = false;
    bool Library1 = false;
    bool Library2 = false;
    bool Library3 = false;
    bool Library4 = false;
    bool Library5 = false;
    bool Library6 = false;
    bool Library7 = false;
    bool Library8 = false;
    bool Library9 = false;
    bool Library10 = false;
}
