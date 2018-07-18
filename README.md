# EasyRP (Custom Discord Rich Presence)

EasyRP is a small program to use the discord-rpc, to make a custom rich presence/game on discord.  
using just an easy config file.

**Usage**
- First you need to register a Rich Presence application with discord
     - Go here https://discordapp.com/developers/applications/me
     - Make a new application **The name of the app will be the main name for the rich presence**
     - Enable rich presence for your app and add some assets
- Download the latest release of EasyRP from here https://github.com/Pizzabelly/EasyRP/releases 
- Edit the config file with the information from your newly registered app
- Run [easyrp binary](https://github.com/Pizzabelly/EasyRP/releases) (it should open a cmd window)
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
