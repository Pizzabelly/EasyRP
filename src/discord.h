#include "discord_rpc.h"
#include "parser.h"

#ifndef DISCORD_H
#define DISCORD_H
void shutdown_discord(int sig);
void update_presence(struct ini_parser* p);
void init_discord(char* client_id);
void refresh_discord();
DiscordRichPresence discordPresence;
#endif
