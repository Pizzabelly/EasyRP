#include <iostream>

bool setPresenceVariables(std::string configPath);

void printVariables(struct config_t c);

//struct type to hold info about the games configuration
struct config_t
{
    // id for the discord developer app 
    std::string clientId;
    // text to show for now playing
    std::string details;
    std::string state;
    // images to show for now playing
    std::pair<std::string, std::string> smallImage;
    std::pair<std::string, std::string> largeImage;
    // timestamps for game; note: these usually have to be within about 24 hours :(
    long long startTimestamp;
    long long endTimestamp;
    
    // Compare this struct to previous struct
    bool compare(struct config_t* p)
    {
        if (p->clientId != clientId) return false;
        else if (p->details != details) return false;
        else if (p->state != state) return false;
        else if (p->smallImage != smallImage) return false;
        else if (p->largeImage != largeImage) return false;
        else if (p->startTimestamp != startTimestamp) return false;
        else if (p->endTimestamp != endTimestamp) return false;
        return true;
    }
};

extern struct config_t config;
