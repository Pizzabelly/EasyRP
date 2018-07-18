#include "config.hpp"
#include "discord.hpp"
#include <chrono>
#include <csignal>
#include <thread>

int main(void) {
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
    initDiscord(config.client_id);

    // loop to keep program running also to check for updated config
    while (true) {
        config.update();
        if (config.changed) {
            // print and set variables for the presence
            config.print();
            updatePresence(&config);
            config.changed = false;
        }
        refreshDiscord();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
