#include "parser.h"
#include "config.h"
#include "discord.h"
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

#define CONFIG_PATH "config.ini"

#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define sleep(x) usleep((x)*1000)
#endif

int main(void) {
    /* define when to shutdown */
    signal(SIGINT, shutdown);
    signal(SIGTERM, shutdown);
#ifdef SIGBREAK
    signal(SIGBREAK, shutdown);
#endif

    struct ini_parser parser;
    if (!load_ini_file(&parser, CONFIG_PATH)) {
       printf("[Error] Failed to load config file\n");
       return 0;
    }
    parse_ini(&parser);

    /* start discord-rpc */
    char* clientid = get_ini_value(&parser, "Identifiers", "ClientID");
    init_discord(clientid);

    /* loop to keep program running also to check for updated config */
    while (true) {
        if (!load_ini_file(&parser, CONFIG_PATH)) {
            printf("[Error] Config file moved or deleted\n");
            shutdown(1);
        }
        parse_ini(&parser);
        if (parser.changed) {
            /* print and set variables for the presence */
            update_presence(&parser);
            parser.changed = false;
        }
        refresh_discord();
        sleep(1000);
    }
    return 0;
}
