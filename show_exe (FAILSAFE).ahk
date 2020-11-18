;-------------------------------------------------------------**SCRIPT WON'T WORK UNTIL YOU EDIT IT ACCORDING TO YOUR NEEDS!**----------------------------------------------------------
;Basically what this script does is that if you get your RP or scripts messed up and wanna MANUALLY close the easyrp.exe file running in hidden mode, the script unhides it for you so that you can close it or whatever.
;---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

;-------------------------------------------------------------------------------**MAIN CODE STARTS HERE**--------------------------------------------------------------------------------

WinShow, ahk_exe easyrp.exe  ;Specify the .exe filename of your easyrp.exe(which is the default filename)-Activates the hidden easyrp.exe file which was running in hidden mode.

ExitApp  ;Terminates the Script.

;---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


;---------------------------------------------------------------**THE CODE WONT WORK WITHOUT INSTALLING AUTOHOTKEY (AHK)**--------------------------------------------------------------
