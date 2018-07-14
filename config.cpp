#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "config.hpp"

#define CONFIG_PATH "config.ini"

// check and set the global presence config 
bool config_t::update()
{
    // open config file
    std::ifstream configFile(CONFIG_PATH);
    
    // bool that is true if any parsed value is different
    bool changed = true;

    // "parse" config file
    // this is super specific and is NOT proper ini parsing
    // but it works, saves memory and avoids massive dependencies
    for (std::string line; std::getline(configFile, line);) 
    {
        // if line is ini comment (;), whitespace, or '[', skip it
        char first = line.front();
        if (first == ';' || first == ' ' || first == '[') continue;

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
                if (key == "ClientID" && value.compare(this->clientId) != 0) 
                	this->clientId = value; 
                else if (key == "State" && value.compare(this->state) != 0)
                    this->state = value; 
                else if (key == "Details" && value.compare(this->details) != 0) 
                    this->details = value; 
                else if (key == "LargeImage" && value.compare(this->largeImg.key) !=0) 
                    this->largeImg.key = value;
                else if (key == "SmallImage" && value.compare(this->smallImg.key) != 0) 
                    this->smallImg.key = value;
                else if (key == "LargeImageTooltip" && value.compare(this->largeImg.text) != 0)
                    this->largeImg.text = value;
                else if (key == "SmallImageTooltip" && value.compare(this->smallImg.text) != 0)
                    this->smallImg.text = value;
                else if (key == "StartTimestamp" && value.compare(std::to_string(this->startTime)) != 0) 
                    this->startTime = std::strtoll(value.c_str(), NULL, 10);
                else if (key == "EndTimestamp" && value.compare(std::to_string(this->endTime)) != 0)
                    this->endTime = std::strtoll(value.c_str(), NULL, 10);
                else changed = false;
            }
        }
    }
    return changed;
}

// print values for the current settings from the config file
void config_t::print()
{
    printf("\nCurrent Presence (%s) :", this->clientId.c_str());
    printf("\nState: %s", this->state.c_str());
    printf("\nDetails: %s", this->details.c_str());
    printf("\nLarge Image: '%s' with toolip, '%s'", this->largeImg.key.c_str(), this->largeImg.text.c_str());
    printf("\nSmall Image: '%s' with toolip, '%s'", this->smallImg.key.c_str(), this->smallImg.text.c_str());
    printf("\nStart Time: %lld", this->startTime);
    printf("\nEnd Time: %lld\n", this->endTime);
}
