# What is UE4 Librarian?

I created this special little DLL to completely remove the need for external DLL Injectors such as [**IGCS/UUU**](https://framedsc.com/GeneralGuides/universal_ue4_consoleunlocker.htm), [**Nefarius Injector**](https://github.com/nefarius/Injector), and all the plentiful of other injectors I've never heard of/used.

This DLL works with Unreal Engine 4.0 - 4.27.2 / But it also works with other versions, it just fails to hook the UnrealModUnlocker *stuff*, which is mostly unrelated to my code.

It's as simple as placing the 'dxgi.dll' into your game's binaries, opening the configuration page 'DList.ini' and setting the DLL Names and their corresponding timer.

# Currently Unfinished
It's finished, but I want to polish it up before counting it as a full release, if you want to use it now you can, you'll have to compile it from source.
By release I plan to remove the UMU hooks altogether, I don't need them and they're only in the way.

You can use this as a DXGI Proxy, or a XInput Proxy. 
You'll have to rename it to to dxgi.dll or xinput1_3.dll

# Credit
Now I will give credit where it's due, **Illusory/ASMRGaming** originally created the proxy code, but nothing else.

[UMU](https://github.com/IllusorySoftware/UnrealModUnlocker-Public)
