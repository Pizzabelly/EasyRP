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
    // open Config File
    std::ifstream configFile(configPath);

    // parse Config File
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
                if (key == "ClientID") config.clientId = value;
                else if (key == "State") config.state = value;
                else if (key == "Details")  config.details = value;
                else if (key == "LargeImage") config.largeImage.first = value;
                else if (key == "SmallImage")  config.smallImage.first = value;
                else if (key == "LargeImageTooltip") config.largeImage.second = value;
                else if (key == "SmallImageTooltip") config.smallImage.second = value;
                else if (key == "StartTimestamp") config.startTimestamp = std::strtoll(value.c_str(), NULL, 10);
                else if (key == "EndTimestamp") config.endTimestamp = std::strtoll(value.c_str(), NULL, 10);
            }
        }
    }
    return true;
}

//Print Values For The Current Settings From The Config File
void printVariables(struct config_t c)
{
    printf("\nCurrent Presence:");
    printf("\nState: %s", c.state.c_str());
    printf("\nDetails: %s", c.details.c_str());
    printf("\nLarge Image: '%s' with toolip, '%s'", c.largeImage.first.c_str(), c.largeImage.second.c_str());
    printf("\nSmall Image: '%s' with toolip, '%s'", c.smallImage.first.c_str(), c.smallImage.second.c_str());
    printf("\nStart Time: %lu", c.startTimestamp);
    printf("\nEnd Time: %lu", c.endTimestamp);
}
