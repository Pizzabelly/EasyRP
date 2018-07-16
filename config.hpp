#include <iostream>

struct pimage_t {
    std::string key;
    std::string text;
};

// struct type to hold info about the games configuration
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
    long long startTime = 0;
    long long endTime = 0;

	// true if presence needs to be updated
	bool changed = true;

   	void update();
   	void print();
};

extern struct config_t config;
