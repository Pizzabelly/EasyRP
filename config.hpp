#include <iostream>

bool setPresenceVariables(std::string configPath);

void printVariables(struct config_t c);

struct pimage_t {
    std::string key;
    std::string text;
};

//struct type to hold info about the games configuration
struct config_t
{
    // id for the discord developer app 
    std::string clientId;
    // text to show for now playing
    std::string details;
    std::string state;
    // images to show for now playing
    pimage_t smallImg;
    pimage_t largeImg;
    // timestamps for game; note: these usually have to be within about 24 hours :(
    long long startTime;
    long long endTime;
   
    /*
    // Compare this struct to previous struct
    bool operator==(const config_t& c, const config_t& p)
    {
        if (p->clientId != c->clientId) return false;
        else if (p->details != c->details) return false;
        else if (p->state != c->state) return false;
        else if (p->smallImage.key != c->smallImage.key) return false;
        else if (p->smallImage.text != c->smallImage.text) return false;
        else if (p->largeImage.key != c->largeImage.key) return false;
        else if (p->largeImage.text != c->largeImage.text) return false;
        else if (p->startTimestamp != c->startTimestamp) return false;
        else if (p->endTimestamp != c->endTimestamp) return false;
        return true;
    }
    */
};

extern struct config_t config;
