#include "config.hpp"
#include "discord.hpp"
#include <algorithm>
#include <fstream>
#include <limits.h>
#include <sstream>

#define CONFIG_PATH "config.ini"

template <class T> T setVar(T val, config_t *c) {
    c->changed = true;
    return val;
}

// check and set the global presence config
void config_t::update() {
    // open config file
    std::ifstream config_file(CONFIG_PATH);
    if (config_file.fail()) {
        printf("config file not found\n");
        Shutdown(1);
    }
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
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
            std::string value;
            if (!std::getline(line_stream, value))
                value = "";
            if (isspace(value.front()) && isspace(value.back()))
                value.erase(0, 1);
            if (key == "ClientID" && value.compare(this->client_id) != 0) {
                this->client_id = setVar<std::string>(value, this);
            } else if (key == "State" && value.compare(this->state) != 0) {
                this->state = setVar<std::string>(value, this);
            } else if (key == "Details" && value.compare(this->details) != 0) {
                this->details = setVar<std::string>(value, this);
            } else if (key == "LargeImage" && value.compare(this->large_img.key) != 0) {
                this->large_img.key = setVar<std::string>(value, this);
            } else if (key == "SmallImage" && value.compare(this->small_img.key) != 0) {
                this->small_img.key = setVar<std::string>(value, this);
            } else if (key == "LargeImageTooltip" &&
                       value.compare(this->large_img.text) != 0) {
                this->large_img.text = setVar<std::string>(value, this);
            } else if (key == "SmallImageTooltip" &&
                       value.compare(this->small_img.text) != 0) {
                this->small_img.text = setVar<std::string>(value, this);
            }

            // special conditions for timestamps to avoid bad values
            else if (key == "StartTimestamp") {
                long long num_value = std::strtoll(value.c_str(), NULL, 10);
                if (num_value != this->start_time)
                    this->start_time = setVar<long long>(num_value, this);
            } else if (key == "EndTimestamp") {
                long long num_value = std::strtoll(value.c_str(), NULL, 10);
                if (num_value != this->end_time)
                    this->end_time = setVar<long long>(num_value, this);
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
