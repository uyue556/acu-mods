ACUFixes-readme.txt

==============================================================================
Installation - experimental Autoloader.
==============================================================================
WARNING: Don't use this method if you have a `version.dll` file in your game folder for some reason
         or _make_a_backup_of_that_file_. You can use the not-autoloader method described further below.
Autoloader technical details:
If you put a DLL file named `version.dll` into your game folder, it should be loaded automatically
when the game starts. This particular DLL will then immediately load the ACUFixes mod.
As a result, your game should start with the mod already loaded every time.
If this works for you, you don't need the ACUFixesLoader.exe file at all.


To install:
Place the files directly into the game's folder.
Game's folder structure will look like this:

    Assassin's Creed Unity/
        ACUFixes/
            ACUFixes.dll
        ...game folders...
        ACU.exe
        version.dll
        ...game files...


To uninstall:
1. Go to the game's folder.
2. Delete the `version.dll`. The mod will not be loaded automatically anymore.
3. Delete the `ACUFixes/` folder.





==============================================================================
Installation - Not-autoloader method:
==============================================================================
Put the ACUFixes.dll and ACUFixesLoader.exe together into any folder and start ACUFixesLoader.exe.
The mod will load in the running ACU.exe process
or the process should be started with mod already loaded.
If you see text in the top left corner of the game window, then the mod has loaded correctly.
On some installations you'll _need_ to run the loader _after_ starting the game.
If that doesn't help, try running as administrator.
If that doesn't help, start the game and run the loader as administrator
while the small picture of the 4 assassins (this picture: https://i.ytimg.com/vi/SF70lY61yGY/hqdefault.jpg)
is visible just before the game window really opens.


==============================================================================
F.A.Q.:
==============================================================================


Q: My antivirus recognizes the mod files as a virus and won't let me run the ACUFixesLoader.exe
A:
You can:
- Add a file exception in your antivirus.
- Use any other DLL injector you like to inject ACUFixes.dll into ACU.exe process.
By the way, here's an explanation as to why the mod files look suspicious:
============
The mod works by modifying the code of the ACU.exe while it's running.
Specifically,
ACUFixes.dll: changes permissions of the code to "writable" and "executable",
              allowing to redirect the game's code to my code and back;
ACUFixesLoader.exe: creates an execution thread in the independent ACU.exe process,
              something that allows to run arbitrary code inside it (tells the game to load the ACUFixes.dll - does nothing else).
These techniques are obviously very useful in doing both good-natured (mods)
and malicious (viruses) programming, and are standard in mods of this kind.
You should be safe, I don't use them for anything outside modifying the ACU.exe
in the ways mentioned in the description.
If it inspires any confidence, the full source code is available for you to read
and build on your own (https://github.com/NameTaken3125/ACUFixes).
I believe there are also techniques for avoiding antiviruses, and I might look into them,
but I just have not had the need to.
============

Q: How do I open the mod menu?
A: Press the keyboard INSERT key.

Q: How to open the mod menu if I don't have INSERT key?
A:
The "Toggle Menu" / "Unload mod" hotkeys can be changed by in the mod menu ("Extra" tab)
or by editing the lines
  "hotkey_ToggleMenu" : "<chosen hotkey here>",
  "hotkey_UnloadMod" : "<chosen hotkey here>",
in the `acufixes-config.json` file.
Replace <chosen hotkey here> with one from the following list:
    KEYBOARD_INSERT
    KEYBOARD_DELETE
    KEYBOARD_PAGEUP
    KEYBOARD_PAGEDOWN
    KEYBOARD_END
    KEYBOARD_HOME
    KEYBOARD_NUMPAD0
    KEYBOARD_NUMPAD1
    KEYBOARD_NUMPAD2
    KEYBOARD_NUMPAD3
    KEYBOARD_NUMPAD4
    KEYBOARD_NUMPAD5
    KEYBOARD_NUMPAD6
    KEYBOARD_NUMPAD7
    KEYBOARD_NUMPAD8
    KEYBOARD_NUMPAD9
    KEYBOARD_NUMPAD_MULTIPLY
    KEYBOARD_NUMPAD_ADD
    KEYBOARD_NUMPAD_SUBTRACT
    KEYBOARD_NUMPAD_DECIMAL
    KEYBOARD_NUMPAD_DIVIDE
    KEYBOARD_F1
    KEYBOARD_F2
    KEYBOARD_F3
    KEYBOARD_F4
    KEYBOARD_F5
    KEYBOARD_F6
    KEYBOARD_F7
    KEYBOARD_F8
    KEYBOARD_F9
    KEYBOARD_F10
    KEYBOARD_F11
    KEYBOARD_F12
    KEYBOARD_F13
    KEYBOARD_F14
    KEYBOARD_F15
    KEYBOARD_F16
    KEYBOARD_F17
    KEYBOARD_F18
    KEYBOARD_F19
    KEYBOARD_F20
    KEYBOARD_F21
    KEYBOARD_F22
    KEYBOARD_F23
    KEYBOARD_F24
    KEYBOARD_0
    KEYBOARD_1
    KEYBOARD_2
    KEYBOARD_3
    KEYBOARD_4
    KEYBOARD_5
    KEYBOARD_6
    KEYBOARD_7
    KEYBOARD_8
    KEYBOARD_9
    KEYBOARD_A
    KEYBOARD_B
    KEYBOARD_C
    KEYBOARD_D
    KEYBOARD_E
    KEYBOARD_F
    KEYBOARD_G
    KEYBOARD_H
    KEYBOARD_I
    KEYBOARD_J
    KEYBOARD_K
    KEYBOARD_L
    KEYBOARD_M
    KEYBOARD_N
    KEYBOARD_O
    KEYBOARD_P
    KEYBOARD_Q
    KEYBOARD_R
    KEYBOARD_S
    KEYBOARD_T
    KEYBOARD_U
    KEYBOARD_V
    KEYBOARD_W
    KEYBOARD_X
    KEYBOARD_Y
    KEYBOARD_Z
    KEYBOARD_BACKSPACE
    KEYBOARD_TAB
    KEYBOARD_CLEAR
    KEYBOARD_ENTER
    KEYBOARD_SHIFT
    KEYBOARD_CTRL
    KEYBOARD_ALT
    KEYBOARD_PAUSE
    KEYBOARD_CAPSLOCK
    KEYBOARD_ESCAPE
    KEYBOARD_SPACE
    KEYBOARD_LEFT
    KEYBOARD_UP
    KEYBOARD_RIGHT
    KEYBOARD_DOWN
    KEYBOARD_SELECT
    KEYBOARD_PRINT
    KEYBOARD_EXECUTE
    KEYBOARD_PRINTSCREEN
    KEYBOARD_HELP
    KEYBOARD_LEFTWINDOWS
    KEYBOARD_RIGHTWINDOWS
    KEYBOARD_APPLICATION
    KEYBOARD_SLEEP
    KEYBOARD_SEPARATOR
    KEYBOARD_NUMLOCK
    KEYBOARD_SCROLLLOCK
    KEYBOARD_LEFTSHIFT
    KEYBOARD_RIGHTSHIFT
    KEYBOARD_LEFTCONTROL
    KEYBOARD_RIGHTCONTROL
    KEYBOARD_LEFTALT
    KEYBOARD_RIGHTALT
    KEYBOARD_BROWSERBACK
    KEYBOARD_BROWSERFORWARD
    KEYBOARD_BROWSERREFRESH
    KEYBOARD_BROWSERSTOP
    KEYBOARD_BROWSERSEARCH
    KEYBOARD_BROWSERFAVORITES
    KEYBOARD_BROWSERHOME
    KEYBOARD_VOLUMEMUTE
    KEYBOARD_VOLUMEDOWN
    KEYBOARD_VOLUMEUP
    KEYBOARD_MEDIANEXTTRACK
    KEYBOARD_MEDIAPREVTRACK
    KEYBOARD_MEDIASTOP
    KEYBOARD_MEDIAPLAYPAUSE
    KEYBOARD_LAUNCHMAIL
    KEYBOARD_LAUNCHMEDIASELECT
    KEYBOARD_LAUNCHAPPLICATION1
    KEYBOARD_LAUNCHAPPLICATION2
    KEYBOARD_OEM1
    KEYBOARD_OEMPLUS
    KEYBOARD_OEMCOMMA
    KEYBOARD_OEMMINUS
    KEYBOARD_OEMPERIOD
    KEYBOARD_OEM2
    KEYBOARD_OEM3
    KEYBOARD_OEM4
    KEYBOARD_OEM5
    KEYBOARD_OEM6
    KEYBOARD_OEM7
    KEYBOARD_OEM8
    KEYBOARD_OEMAX
    KEYBOARD_OEM102
    KEYBOARD_ICOHELP
    KEYBOARD_ICO00
    KEYBOARD_PROCESSKEY
    KEYBOARD_ICOCLEAR
    KEYBOARD_PACKET
    KEYBOARD_OEMRESET
    KEYBOARD_OEMJUMP
    KEYBOARD_OEMPA1
    KEYBOARD_OEMPA2
    KEYBOARD_OEMPA3
    KEYBOARD_OEMWSCTRL
    KEYBOARD_OEMCUSEL
    KEYBOARD_OEMATTN
    KEYBOARD_OEMFINISH
    KEYBOARD_OEMCOPY
    KEYBOARD_OEMAUTO
    KEYBOARD_OEMENLW
    KEYBOARD_OEMBACKTAB
    KEYBOARD_ATTN
    KEYBOARD_CRSEL
    KEYBOARD_EXSEL
    KEYBOARD_EREOF
    KEYBOARD_PLAY
    KEYBOARD_ZOOM
    KEYBOARD_NONAME
    KEYBOARD_PA1
    KEYBOARD_OEMCLEAR

Q: How to disable the overlay text in the top left corner?
A:
Untick the checkbox 'Show the "is injected" indicator' in the "Extra" tab in mod menu
or set
  "imgui_showSuccessfulInjectionIndicator" : false,
in the `acufixes-config.json` file.
