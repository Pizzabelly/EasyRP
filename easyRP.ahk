#NoTrayIcon
#Persistent
#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

Time := A_NowUTC
EnvSub, Time, 19700101000000, Seconds

Run, C:\Program Files\AutoHotkey\SciTE\SciTE.exe
WinWait, ahk_class SciTEWindow


if WinExist(ahk_class SciTEWindow)
	{
		FileDelete, C:\Discord-Rich Presence\RP-SciTE4 AHK\config.ini

		FileAppend,
			(		
				[Identifiers]
				ClientID=764184934192513044

				[State]
				State=AHK File
				Details=Editing a Script
				StartTimestamp= %Time%
				EndTimestamp= 

				[Images]
				LargeImage=scite4
				LargeImageTooltip=Updating AutoHotKey
				SmallImage=ahk
				SmallImageTooltip=AHK
			), C:\Discord-Rich Presence\RP-SciTE4 AHK\config.ini
		
		Run, C:\Discord-Rich Presence\RP-SciTE4 AHK\scite.exe, ,Hide
	}


WinWaitClose, ahk_class SciTEWindow

WinShow, ahk_class ConsoleWindowClass ahk_exe scite.exe
WinClose, ahk_class ConsoleWindowClass ahk_exe scite.exe
	
WinWaitClose, ahk_class ConsoleWindowClass ahk_exe scite.exe
	
ExitApp