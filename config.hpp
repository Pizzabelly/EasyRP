#include <iostream>

struct pimage_t {
    std::string key;
    std::string text;
};

// struct type to hold info about the games configuration
struct config_t {
    // id for the discord developer app
    std::string client_id;

    // text to show for now playing
    std::string details;
    std::string state;

    // images to show for now playing
    pimage_t small_img;
    pimage_t large_img;

    // timestamps for game; note: these usually have to be within about 24 hours
    // :(
    long long start_time = 0;
    long long end_time = 0;

    // true if presence needs to be updated
    bool changed = true;

    void update();
    void print();
};

extern struct config_t config;
