#include <iostream>

bool checkValidValue(std::string value);

bool setPresenceVariables(std::string configPath);

bool configFileChanged(std::string configPath);

void printVariables();

extern std::string clientID;
extern std::string state;
extern std::string details;
extern std::string smallImage;
extern std::string largeImage;
extern std::string largeImageText;
extern std::string smallImageText;
extern std::string startTimestamp;
extern std::string endTimestamp;

