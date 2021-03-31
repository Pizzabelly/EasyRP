-------------------------------------------EasyRP (Custom Discord Rich Presence)https://github.com/Pizzabelly/EasyRP----------------------------------------
1. First you need to register a Rich Presence application with discord
     - Go here https://discordapp.com/developers/applications/me
     - Make a new application **The name of the app will be the main name for the rich presence**
     - Enable rich presence for your app and add some assets
2 Download the latest release of EasyRP from here https://github.com/Pizzabelly/EasyRP/releases 
3 Edit the config file with the information from your newly registered app
4 Run easyrp (it should open a cmd window)
    - It *should* report errors from your config file (if there are any)
5 Discord should show the game on your profile
	- if not, add the exe as a game on discord and the file path should change to your presence

You can edit the config any time while the program is running to change the presence (make sure to save the file)



------------------------------------------------------Automation (Provided by bBSempai)https://github.com/bBSempai------------------------------------------------
1.Upon running an AHK script you can automate your tasks. In order to do this follow the steps above but you don't need to edit the config file yet.
2.Install AHK (Takes up <15 Mb worth of space). Your .ahk scripts would not work without installing this.
3.After downloading the EasyRP release with the AHK scripts configure the .ahk scripts according to the guidelines provided in each one of them. Please make sure you edit the scripts properly.

=>Basically the main script easyRP.ahk does something like this:
1)Upon running the script it first opens up the application for you of which you want to show the RP of.
2)Next it rewrites the config.ini file with the information provided by you in the script about the app. This task is necessary because upon doing this easyRP will automatically display the Timestamp to your RP on discord and it will reset everytime you re-run the script. Something which previously had to be done manually through the Epoch timestamp thingy.
3)After setting up the config.ini it runs the easyrp.exe file in hidden mode which ultimately is responsible for your app RP display on discord.
4)Finally the script waits till you close your app. As soon as you do that the script closes the easyrp.exe file which was running in hidden mode and terminates the script.
The script itself runs in a hidden mode so you don't have to worry about anything now!

Just make different scripts for different apps and then run THOSE SCRIPTS INSTEAD OF INDIVIDUALLY RUNNING YOUR APPS, CONFIGURING THE ini FILE, RUNNING THE easyrp.exe AND THEN CLOSING IT MANUALLY AFTER YOU CLOSE YOUR APP. That ONE Script will do all of that for you!

The Failsafe.ahk is provided to you as a precaution. If for some reason you want to close the exe file running in the hidden mode, you won't be able to normally cuz DUH, its hidden lol. So you could go Task Manager and End Task it. Instead you can also simply run this script and it will unhide that exe file for you. The script can preferably also be used to check if any IDLE EXEs are running around, it that ever happpnes.
