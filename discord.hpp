void updatePresence(const char* state, const char* details, long long startTimestamp, long long endTimestamp, const char* smallImageKey,
        const char* smallImageText, const char* largeImageKey, const char* largeImageText);

void InitDiscord(const char* clientID);

void Shutdown(int sig);
