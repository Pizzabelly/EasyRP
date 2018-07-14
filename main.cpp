#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include "config.hpp"
#include "discord.hpp"

#define CONFIG_PATH "config.ini"

bool force_update = true;

// loop to keep the program running as well as checking the config file for updates
int main(void)
{
    // define when to shutdown
    signal(SIGINT, Shutdown);
    signal(SIGTERM, Shutdown);
#ifdef SIGBREAK
    signal(SIGBREAK, Shutdown);
#endif

	// main config instance
	config_t config;
    config.update();

    // start discord-rpc
    InitDiscord(config.clientId);
   
    // loop to keep program running also to check for updated config
    do
    {
        if (config.update() || force_update)
        { 
            // print and set variables for the presence
            config.print();
            updatePresence(&config);
        }
        if (force_update) force_update = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    while(true);

    return 0;
}

