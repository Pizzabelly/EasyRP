#include "config.hpp"
#include "discord.hpp"
#include <iostream>
#include <windows.h>
#include <csignal>

#define CONFIG "config.ini"

//quit for stopping the loop
//firstUpdate to update without changing the config (first loop only)
bool quit = false;
bool firstUpdate = true;

//Break the loop and properly shutdown discord-rp
void shutdown_signal(int sig)
{
    signal(sig, shutdown_signal);
    Shutdown();
    quit = true;
}

//Loop to keep the program running as well as checking the config file for updates
int main(void)
{
    //Define When to Shutdown
    signal(SIGINT, shutdown_signal);
    signal(SIGTERM, shutdown_signal);
#ifdef SIGBREAK
    signal(SIGBREAK, shutdown_signal);
#endif
   
    //Grab initial variables from the config 
    setPresenceVariables(CONFIG);
    //Start discord-rp
    InitDiscord(clientID.c_str());
    
    //Loop to keep program running also to check for updated config
    while(!quit)
    {
        if (configFileChanged(CONFIG) || firstUpdate)
        {
            //Print and set variables for the presence
            printVariables();
            UpdatePresence(state.c_str(), details.c_str(), largeImage.c_str(),
                    smallImage.c_str(), smallImageText.c_str(), largeImageText.c_str());
            //Switch firstUpdate as it is not the first update anymore ;)
            if (firstUpdate)
                firstUpdate = false;
        }
        Sleep(10000);
    }
    return 0;
}

