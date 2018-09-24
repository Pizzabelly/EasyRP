#include "discord.h"
#include <limits.h>
#include <stdio.h>

/* print values for the current settings from the config file */
void print_config_values(DiscordRichPresence* d, char* client_id) {
    printf("Current Presence (%s) :\n", client_id);
    printf("State: %s\n", d->state);
    printf("Details: %s\n", d->details);
    printf("Large Image: '%s' with toolip, '%s'\n", d->largeImageKey,
           d->largeImageText);
    printf("Small Image: '%s' with toolip, '%s'\n", d->smallImageKey,
           d->smallImageText);
    printf("Start Time: %ld\n", d->startTimestamp);
    printf("End Time: %ld\n", d->endTimestamp);
}
