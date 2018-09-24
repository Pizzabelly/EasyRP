#include "discord_rpc.h"
#include "parser.h"

void update_presence(struct ini_parser* p);
void init_discord(char* client_id);
void refresh_discord();
void shutdown(int sig);
DiscordRichPresence discordPresence;
