#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <cstring>
#include "discord_rpc.h"
#include "config.hpp"

// handle discord ready event
static void handleDiscordReady(const DiscordUser* u)
{
    printf("\nDiscord: ready\n");
}

// handle discord disconnected event
static void handleDiscordDisconnected(int errcode, const char* message)
{
    printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}

// handle discord error event
static void handleDiscordError(int errcode, const char* message)
{
    printf("\nDiscord: error (%d: %s)\n", errcode, message);
}

// shutdown discord-rpc
void Shutdown(int sig)
{
    printf("\nshutting down...\n");
    Discord_Shutdown();
    exit(sig);
}

// update discord rich presence
void updatePresence(config_t* c)
{
    // set required variables
    char buffer[256];
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));

    // make sure required parameters are set, if not dont update untill they are corrected 
    // TODO: find the actual character limit for state and details
    if (c->state.length() < 1 || c->state.length() > 100)
    {
        printf("\nState parameter is too long or not set\nPress any key to exit...\n");
        return;
    }

    if (c->details.length() < 1 || c->details.length() > 100)
    {
        printf("\nDetails parameter is too long or not set\nPress any key to exit...\n");
        return;
    }
    if (c->largeImg.key.length() < 1 || c->largeImg.key.length() > 100)
    {
        printf("\nLargeImage parameter not set\nPress any key to exit...\n");
        return;
    }

    discordPresence.state = c->state.c_str();
    discordPresence.largeImageKey = c->largeImg.key.c_str();
    sprintf(buffer, "%s", c->details.c_str());
    discordPresence.details = buffer;

    if (c->startTime >= 0) discordPresence.startTimestamp = (int64_t)c->startTime;
    if (c->endTime >= 0) discordPresence.endTimestamp = (int64_t)c->endTime;

    // make sure not to set the optional variables if they are not defined in the config
    if (c->smallImg.key.length() >= 1) discordPresence.smallImageKey = c->smallImg.key.c_str();
    if (c->smallImg.text.length() >= 1) discordPresence.smallImageText = c->smallImg.text.c_str();
    if (c->largeImg.text.length() >= 1) discordPresence.largeImageText = c->largeImg.text.c_str();

    // actaully update the presence
    Discord_UpdatePresence(&discordPresence);
}

// initialize discord rich presence
void InitDiscord(std::string clientId)
{
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.errored = handleDiscordError;
    handlers.disconnected = handleDiscordDisconnected;
    if (clientId.length() < 1 || clientId == "123456789012345678")
    {
        printf("ClientID not correct (or not set), unless by god you \
somehow got 123456789012345678 as your clientid please change \
this to the one you registered on the website");
        Shutdown(1);
    }
    Discord_Initialize(clientId.c_str(), &handlers, 1, NULL);
}

