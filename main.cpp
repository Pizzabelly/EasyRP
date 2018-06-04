#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include "config.hpp"
#include "discord.hpp"

#define CONFIG_PATH "config.ini"

//Loop to keep the program running as well as checking the config file for updates
int main(void)
{
    //Define When to Shutdown
    signal(SIGINT, Shutdown);
    signal(SIGTERM, Shutdown);
#ifdef SIGBREAK
    signal(SIGBREAK, Shutdown);
#endif

    config_t prevConfig = config;
    setPresenceVariables(CONFIG_PATH);

    //Start discord-rpc
    InitDiscord(config.clientId.c_str());
   
    //Loop to keep program running also to check for updated config
    do
    {
        if (!config.compare(&prevConfig))
        { 
            //Print and set variables for the presence
            printVariables(config);
            updatePresence(config.state.c_str(), config.details.c_str(), config.startTimestamp, config.endTimestamp,
                    config.smallImage.first.c_str(), config.smallImage.second.c_str(), 
                    config.largeImage.first.c_str(), config.largeImage.second.c_str());
        }
        prevConfig = config;
        setPresenceVariables(CONFIG_PATH);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    while(true);

    return 0;
}

