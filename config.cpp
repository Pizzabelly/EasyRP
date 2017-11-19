#include <sstream>
#include <iostream>
#include <windows.h>
#include <regex>
#include <fstream>
#include <algorithm>

//Initialize Possible Properties For The Presence
std::string clientID;
std::string state;
std::string details;
std::string smallImage;
std::string largeImage;
std::string largeImageText;
std::string smallImageText;

//Regex Patern To Check Certian Variables
bool checkValidValue(std::string value)
{
    std::regex r("^[a-zA-Z-1-9_.-]*");
    std::smatch m;
    if (std::regex_search(value, m, r))
        return true;
    return false;
}

//Check and Set The Global Presence Variables
bool setPresenceVariables(std::string configPath)
{
    //Open Config File
    std::ifstream config(configPath);

    //Parse Config File
    std::string line;
    while(std::getline(config, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '='))
        {
            std::string value;
            if (std::getline(is_line, value))
            {
                if (key == "ClientID")
                    clientID = value;
                else if (key == "State")
                    state = value;
                else if (key == "Details")
                    details = value;
                else if (key == "LargeImage")
                    largeImage = value;
                else if (key == "SmallImage")
                    smallImage = value;
                else if (key == "LargeImageTooltip")
                    largeImageText = value;
                else if (key == "SmallImageTooltip")
                    smallImageText = value;
            }
        }
    }

    //Check Certian Variables Against The Same(?) Regex as discord
    std::string checkableValues[2] = {largeImage, smallImage};
    for(std::string value : checkableValues)
    {
        if (!checkValidValue(value))
        {
            std::cout << value + " is NOT valid for a image key" << std::endl;
            return false;
        }
    }
    return true;
}

//Print Values For The Current Settings From The Config File
void printVariables()
{
    std::cout << "\nCURRENT SETTINGS" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "STATE IS: " + state << std::endl;
    std::cout << "DETAILS ARE: " + details << std::endl;
    std::cout << "LARGE IMAGE IS: " + largeImage << std::endl;
    std::cout << "SMALL IMAGE IS: " + smallImage << std::endl;
    std::cout << "SMALL IMAGE TEXT IS: " + smallImageText << std::endl;
    std::cout << "LARGE IMAGE TEXT IS: " + largeImageText << std::endl;
}

//Check If Config File Updated
bool configFileChanged(std::string configPath)
{
    std::string vars[7] = {clientID, state, details, largeImage, smallImage, smallImageText, largeImageText};
    if (setPresenceVariables(configPath))
    {
        std::string possibleUpdatedVars[7] = {clientID, state, details, largeImage, smallImage, smallImageText, largeImageText};
        for(int i = 0; i < 7; i++)
        {
            if (vars[i] != possibleUpdatedVars[i])
                return true;
        }
    }
    return false;
}








