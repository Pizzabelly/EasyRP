#include "config.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#define CONFIG_PATH "config.ini"

std::string setVar(std::string val, config_t *c) {
    c->changed = true;
    return val;
}

// check and set the global presence config
void config_t::update() {
    // open config file
    std::ifstream config_file(CONFIG_PATH);

    // "parse" config file
    // this is super specific and is NOT proper ini parsing
    // but it works, saves memory and avoids massive dependencies
    for (std::string line; std::getline(config_file, line);) {
        // if line is ini comment (;), whitespace, or '[', skip it
        char first = line.front();
        if (first == ';' || first == ' ' || first == '[')
            continue;

        std::istringstream line_stream;
        line_stream.str(line);

        std::string key;
        if (std::getline(line_stream, key, '=')) {
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace),
                      key.end());
            std::string value;
            if (std::getline(line_stream, value)) {
                if (isspace(value.front()))
                    value.erase(0, 1);
                if (key == "ClientID" && value.compare(this->client_id) != 0)
                    this->client_id = setVar(value, this);
                else if (key == "State" && value.compare(this->state) != 0)
                    this->state = setVar(value, this);
                else if (key == "Details" && value.compare(this->details) != 0)
                    this->details = setVar(value, this);
                else if (key == "LargeImage" &&
                         value.compare(this->large_img.key) != 0)
                    this->large_img.key = setVar(value, this);
                else if (key == "SmallImage" &&
                         value.compare(this->small_img.key) != 0)
                    this->small_img.key = setVar(value, this);
                else if (key == "LargeImageTooltip" &&
                         value.compare(this->large_img.text) != 0)
                    this->large_img.text = setVar(value, this);
                else if (key == "SmallImageTooltip" &&
                         value.compare(this->small_img.text) != 0)
                    this->small_img.text = setVar(value, this);
                else if (key == "StartTimestamp" &&
                         value.compare(std::to_string(this->start_time)) != 0)
                    this->start_time =
                        std::strtoll(setVar(value, this).c_str(), NULL, 10);
                else if (key == "EndTimestamp" &&
                         value.compare(std::to_string(this->end_time)) != 0)
                    this->end_time =
                        std::strtoll(setVar(value, this).c_str(), NULL, 10);
            }
        }
    }
}

// print values for the current settings from the config file
void config_t::print() {
    printf("\nCurrent Presence (%s) :", this->client_id.c_str());
    printf("\nState: %s", this->state.c_str());
    printf("\nDetails: %s", this->details.c_str());
    printf("\nLarge Image: '%s' with toolip, '%s'", this->large_img.key.c_str(),
           this->large_img.text.c_str());
    printf("\nSmall Image: '%s' with toolip, '%s'", this->small_img.key.c_str(),
           this->small_img.text.c_str());
    printf("\nStart Time: %lld", this->start_time);
    printf("\nEnd Time: %lld\n", this->end_time);
}
