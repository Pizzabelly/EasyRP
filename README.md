# EasyRP (Custom Discord Rich Presence)

EasyRP is a small program to use the DiscordRPC library without any knowledge of programming.
Instead just use an easy conifg file

**Usage**
- First you need to register a Rich Presence application with discord
     - Go here https://discordapp.com/developers/applications/me
     - Make a new application **The name of the app will be the main name for the rich presence**
     - Enable rich presence for your app and add some assets
- Download the latest release of EasyRP from here https://github.com/Pizzabelly/EasyRP/releases
- Edit the config file with the information from your newly registered app

[Identifiers]
- ClientID=(clientidhere)
State=(subtext here)
Details=(headertext here)

[Images]
LargeImage=(largeimagename here)
SmallImage=(smallimagename here)
LargeImageTooltip=(largeimagecontext here)
SmallImageTooltip=(smallimagecontext here)

**EXPLANATION:** The clientID is the value at the top of your Rich Presence application. The images are supposed to be uploaded as assets in the Rich Presence application you've made. Then, input the name of the assets in the config file. The tooltips are basically the text that appears when you hover over it. The state and details are the text that appears under the images.

- Run [EasyRP.exe](https://github.com/Pizzabelly/EasyRP/releases) (it should open a cmd window)
    - It should report errors from your config file (if there are any)
- Go into discord settings and add the [EasyRP.exe](https://github.com/Pizzabelly/EasyRP/releases) as a game
- Discord should automatically change the path of [EasyRP.exe](https://github.com/Pizzabelly/EasyRP/releases) to your Discord Rich Presence

- You can edit the config any time while the program is running to change the presence
