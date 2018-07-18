#include "config.hpp"
#include <cstring>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <string>

#define DISCORD_DISABLE_IO_THREAD
#include "discord_rpc.h"

// shutdown discord-rpc
void Shutdown(int sig) {
    printf("\nshutting down...\n");
    Discord_Shutdown();
    getchar();
    exit(sig);
}

// handle discord ready event
void handleDiscordReady(const DiscordUser *u) {
    printf("\nDisplaying Presence for %s#%s\n", u->username, u->discriminator);
}

// handle discord disconnected event
void handleDiscordDisconnected(int errcode, const char *message) {
    printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}

// handle discord error event
void handleDiscordError(int errcode, const char *message) {
    printf("\nDiscord: error (%d: %s)\n", errcode, message);
    Shutdown(1);
}

// update discord rich presence
void updatePresence(config_t *c) {
    // set required variables
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));

    // make sure required parameters are set, if not dont update untill they are
    // corrected
    // TODO: find the actual character limit for state and details
    if (c->state.length() < 1 || c->state.length() > 100) {
        printf("\nState parameter is too long or not set\n");
        return;
    }
    if (c->details.length() < 1 || c->details.length() > 100) {
        printf("\nDetails parameter is too long or not set\n");
        return;
    }
    if (c->large_img.key.length() < 1 || c->large_img.key.length() > 100) {
        printf("\nLargeImage parameter not set\n");
        return;
    }

    discordPresence.state = c->state.c_str();
    discordPresence.largeImageKey = c->large_img.key.c_str();
    char buffer[256];
    sprintf(buffer, "%s", c->details.c_str());
    discordPresence.details = buffer;

    if (c->start_time == LLONG_MAX || c->start_time == LLONG_MIN ||
        c->end_time == LLONG_MAX || c->end_time == LLONG_MIN) {
        printf("wew!, one (or both) of your timestamps is WAY too big");
        return;
    }

    if (c->start_time >= 0 && c->start_time != 0LL)
        discordPresence.startTimestamp = (int64_t)c->start_time;
    if (c->end_time >= 0 && c->end_time != 0LL)
        discordPresence.endTimestamp = (int64_t)c->end_time;

    // dont set optional variables if they are not defined in the config
    if (c->small_img.key.length() >= 1)
        discordPresence.smallImageKey = c->small_img.key.c_str();
    if (c->small_img.text.length() >= 1)
        discordPresence.smallImageText = c->small_img.text.c_str();
    if (c->large_img.text.length() >= 1)
        discordPresence.largeImageText = c->large_img.text.c_str();

    // actaully update the presence
    Discord_UpdatePresence(&discordPresence);
}

void refreshDiscord() {
    // manually handle this
    Discord_UpdateConnection();

    // callbacks
    Discord_RunCallbacks();
}

// initialize discord rich presence
void initDiscord(std::string client_id) {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.errored = handleDiscordError;
    handlers.disconnected = handleDiscordDisconnected;
    if (client_id.length() < 1 || client_id.compare("123456789012345678") == 0) {
        printf("ClientID not correct (or not set).\nUnless by god you somehow "
               "got 123456789012345678 as your clientid please change this to "
               "the one you registered on the website");
        Shutdown(1);
    }
    Discord_Initialize(client_id.c_str(), &handlers, 1, NULL);
}
