#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include "discord.h"
#include "parser.h"

#define CONFIG_PATH "config.ini"

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(x)
#else
#include <unistd.h>
#define sleep(x) usleep((x)*1000)
#endif

int main(void) {
  /* define when to shutdown */
  signal(SIGINT, shutdown_discord);
  signal(SIGTERM, shutdown_discord);

  struct ini_parser parser;
  if (!load_ini_file(&parser, CONFIG_PATH)) {
    printf("[Error] Failed to load config file\n");
    return 0;
  }

  parser.data.max_count = 0;
  parse_ini(&parser);

  /* start discord-rpc */
  char* client_id = get_ini_value(&parser, "Identifiers", "ClientID");
  init_discord(client_id);

  /* loop to keep program running also to check for updated config */
  while (true) {
    if (!load_ini_file(&parser, CONFIG_PATH)) {
      printf("[Error] Config file moved or deleted\n");
      shutdown_discord(1);
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
