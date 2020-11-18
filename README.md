# EasyRP (Custom Discord Rich Presence)

EasyRP is a small program to use the discord-rpc, to make a custom rich presence/game on discord.  
using just an easy config file.

## Usage
- First you need to register a Rich Presence application with discord
     - Go here https://discordapp.com/developers/applications/me
     - Make a new application **The name of the app will be the main name for the rich presence**
     - Enable rich presence for your app and add some assets
- Download the latest release of EasyRP from here https://github.com/Pizzabelly/EasyRP/releases 
  - if you are on Windows you also need [Visual C++ Redistributable](https://www.microsoft.com/en-US/download/details.aspx?id=48145)  
- Edit the config file with the information from your newly registered app
- Run the [EasyRP executable](https://github.com/Pizzabelly/EasyRP/releases) (it should open a cmd window)
    - It *should* report errors from your config file (if there are any)
- Discord should show the game on your profile
	- if not, add the exe as a game on discord and the file path should change to your presence

- You can edit the config any time while the program is running to change the presence (make sure to save the file)
 
**Timestamps**  
The Start and End timestamps are in epoch/unix time. 
Your desired values can be found [here](https://www.epochconverter.com/).
For elapsed time set only the StartTimestamp. For remaining time set both.
Though discord seems to only care about hours/minutes/seconds.
As it doesnt go above 24hrs either way ¯\\\_(ツ)\_/¯

## Automation (Provided by [bBSempai](https://github.com/bBSempai))

- Upon running an AHK script you can automate your tasks. In order to do this follow the steps above but you don't need to edit the config file yet.
- Install [AHK](https://www.autohotkey.com/) (Takes up <15 Mb worth of space). Your .ahk scripts would not work without installing this.
- After downloading the [EasyRP release](https://github.com/Pizzabelly/EasyRP/releases) with the AHK scripts **configure the .ahk scripts according to the guidelines provided in each one of them. Please make sure you edit the scripts properly.**<br><br>
- Basically the main script [easyRP.ahk](https://github.com/Pizzabelly/EasyRP/blob/master/easyRP.ahk) does something like this:
	- Upon running the script it first opens up the application for you of which you want to show the RP of.
	- Next it rewrites the config.ini file with the information provided by you in the script about the app. **This task is necessary because upon doing this easyRP will automatically display the Timestamp to your RP on discord and it will reset everytime you re-run the script. Something which previously had to be done manually through the Epoch timestamp thingy.**
	- After setting up the config.ini it runs the easyrp.exe file in hidden mode which ultimately is responsible for your app RP display on discord.
	- Finally the script waits till you close your app. As soon as you do that the script closes the easyrp.exe file which was running in hidden mode and terminates the script.
	- The script itself runs in a hidden mode so you don't have to worry about anything now!<br><br>Just make different scripts for different apps and then run THOSE SCRIPTS INSTEAD OF INDIVIDUALLY RUNNING YOUR APPS, CONFIGURING THE ini FILE, RUNNING THE easyrp.exe AND THEN CLOSING IT MANUALLY AFTER YOU CLOSE YOUR APP. That ONE Script will do all of that for you!<br><br>
- The [Failsafe.ahk](https://github.com/Pizzabelly/EasyRP/blob/master/show_exe%20(FAILSAFE).ahk) is provided to you as a precaution. If for some reason you want to close the exe file running in the hidden mode, you won't be able to normally cuz DUH, its hidden lol. So you could go Task Manager and End Task it. Instead you can also simply run this script and it will unhide that exe file for you. **The script can preferably also be used to check if any IDLE EXEs are running around, it that ever happpnes.**

<p align=center>
   <img src="https://i.imgur.com/YsGjddb.png" width="30%" />
   <img src="https://i.imgur.com/NdAd3Wq.png" width="30%" />
   <img src="https://i.imgur.com/WbHfCZ5.png" width="30%" />
</p>

Now, running the AHK script instead of your App can be confusing and cumbersome. What you can do is change the ICONS of the individual scripts to those of your apps so that it would look like you are actually running that app itself.
<p align=center>
<img src ="https://i.imgur.com/0H68318.png" >
<br>Something like this
</p>

**Note: You can always manually control the easyrp.exe and the .ahk files from the Task Manager window if any issues occur.**<br><p align=center>Also AHK isn't still supported by Linux :(</p>

## Building  
To build EasyRP from source you need the following
  - any c++ compiler (cl, g++, clang++, etc)
  - Meson
  - Ninja
  - CMake (for discord-rpc library)  
  
Build discord-rpc  
  - ``` git clone https://github.com/Pizzabelly/EasyRP --recurse-submodules ```  
  - ``` cd EasyRP/discord-rpc ```  
  - ``` mkdir build && cd build ```  
  - ``` cmake .. -DENABLE_IO_THREAD=OFF ``` -DENABLE_IO_THREAD option will prevent a link error (see [#49](https://github.com/Pizzabelly/EasyRP/issues/49))  
  
Now depending on your platform building the discord-rpc library will be different  
  - Unix: ``` make ```  
  - Windows (visual studio): ``` msbuild /p:Configuration=Release ```  
  - Windows (mingw): ``` mingw32-make.exe ```  
Now the library should be under src/[lib]discord-rpc.[lib|a], move that to the root of the EasyRP repo  
  
To build EasyRP (in the root of the repo)  
  - ``` meson --buildtype=release build ```  
  - ``` ninja -C build ```  
  
Now the EasyRP executable will be under the build directory!
<br><br>

<p align="center">Feel free to contact us regarding anything you need help with!</p>

<p align="center">
  <a href="https://GitHub.com/Pizzabelly/EasyRP/issues/new"><b><i>Feel free to open an issue and communicate!</i></b><br></a>
</p>
