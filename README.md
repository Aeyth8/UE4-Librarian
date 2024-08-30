# What is UE4 Librarian?

I created this special little DLL to completely remove the need for external DLL Injectors such as [**IGCS/UUU**](https://framedsc.com/GeneralGuides/universal_ue4_consoleunlocker.htm), [**Nefarius Injector**](https://github.com/nefarius/Injector), and all the plentiful of other injectors I've never heard of/used.

This DLL works with Unreal Engine 4.0 - 4.27.2 / But it also works with other versions, it just fails to hook the UnrealModUnlocker *stuff*, which is mostly unrelated to my code.

It's as simple as placing the 'dxgi.dll' into your game's binaries, opening the configuration page 'DList.ini' and setting the DLL Names and their corresponding timer.

# Currently Unfinished
It just needs a small fix and a couple changes and it will be ready for use!

# Credit
Now I will give credit where it's due, **Illusory/ASMRGaming** originally created this project and code, but he discontinued going the open source route and ended up going into the closed-off scumbag gatekeeper routine, making his special little "Mod Unlocker" both closed source, and locked behind a paywall. 

Now I don't really know the guy much, but I've had a personal encounter with him that's made me grow unfond of him (and I actually used to have respect for the guy). 

*(no idea if he made the whole thing or just parts of it, I don't know and I don't care)*

~~Oops I forgor to fork~~ ~~https://github.com/IllusorySoftware/UnrealModUnlocker-Public~~
