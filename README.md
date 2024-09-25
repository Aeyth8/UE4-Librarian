# What is UE4 Librarian?

I created this special little DLL to completely remove the need for external DLL Injectors such as [**IGCS/UUU**](https://framedsc.com/GeneralGuides/universal_ue4_consoleunlocker.htm), [**Nefarius Injector**](https://github.com/nefarius/Injector), and all the plentiful of other injectors I've never heard of/used.

This DLL works with Unreal Engine 4 & 5, I have not yet tested it with older versions.

It's as simple as placing the ``dxgi.dll`` or ``xinput1_3.dll`` into your game's binaries, launching the game once to create the config, opening the config file ``DList.ini`` and setting the DLL Names and their corresponding timer.

*(Of course you'll also want to place whatever DLLs that you want injected into the binaries folder)*

# Currently Unfinished
It's a work in progress **(WIP)** 

The program is fully functional and will be improved in the future.

You can use this as a DXGI Proxy, or a XInput Proxy. 

You'll have to name it ``dxgi.dll`` or ``xinput1_3.dll``

# Credit
Now I will give credit where it's due, **Illusory/ASMRGaming** created **ONLY** the proxy code.

[UMU](https://github.com/IllusorySoftware/UnrealModUnlocker-Public)
