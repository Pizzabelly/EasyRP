#include <sstream>
#include <iostream>
#include <regex>
#include <fstream>
#include <bits/stl_algo.h>
#include <algorithm>
#include "config.hpp"

// config_t instance for holding info for the presence
config_t config;

// check and set the global presence config 
bool setPresenceVariables(std::string configPath)
{
    // open config file
    std::ifstream configFile(configPath);
    
    // bool that is true if any parsed value is different
    bool changed = false;

    // parse config file
    for (std::string line; std::getline(configFile, line);) 
    {
        // if line is ini comment (;) skip it
        if (line.front() == ';') continue;
        
        std::istringstream line_stream;
        line_stream.str(line);

        std::string key;
        if (std::getline(line_stream, key, '='))
        {
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
            std::string value;
            if (std::getline(line_stream, value)) 
            { 
                if (isspace(value.front())) value.erase(0, 1);
                if (key == "ClientID" && value.compare(config.clientId) != 0) { config.clientId = value; changed = true; }
                else if (key == "State" && value.compare(config.state) != 0) { config.state = value; changed = true; }
                else if (key == "Details" && value.compare(config.details) != 0) { config.details = value; changed = true; }
                else if (key == "LargeImage" && value.compare(config.largeImg.key) !=0 ) { config.largeImg.key = value; changed = true; }
                else if (key == "SmallImage" && value.compare(config.smallImg.key) != 0) { config.smallImg.key = value; changed = true; }
                else if (key == "LargeImageTooltip" && value.compare(config.largeImg.text) != 0) { config.largeImg.text = value; changed = true; }
                else if (key == "SmallImageTooltip" && value.compare(config.smallImg.text) != 0) { config.smallImg.text = value; changed = true; } 
                else if (key == "StartTimestamp" && value.compare(std::to_string(config.startTime)) != 0) { config.startTime = std::strtoll(value.c_str(), NULL, 10); changed = true; }
                else if (key == "EndTimestamp" && value.compare(std::to_string(config.endTime)) != 0) { config.endTime = std::strtoll(value.c_str(), NULL, 10); changed = true; }
            }
        }
    }
    return changed;
}

// print values for the current settings from the config file
void printVariables(struct config_t* c)
{
    printf("\nCurrent Presence (%s) :", c->clientId.c_str());
    printf("\nState: %s", c->state.c_str());
    printf("\nDetails: %s", c->details.c_str());
    printf("\nLarge Image: '%s' with toolip, '%s'", c->largeImg.key.c_str(), c->largeImg.text.c_str());
    printf("\nSmall Image: '%s' with toolip, '%s'", c->smallImg.key.c_str(), c->smallImg.text.c_str());
    printf("\nStart Time: %lld", c->startTime);
    printf("\nEnd Time: %lld\n", c->endTime);
}
