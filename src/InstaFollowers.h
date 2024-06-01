#ifndef InstaFollowers_h
#define InstaFollowers_h

#include "Arduino.h"
#define bufferSize 300 //you can adjust that if you want to.

class InstaFollowers {
public:
    InstaFollowers(String host, String ApiKey);
    int GetUserFollowersCount(String username);
    int GetUserFollowingCount(String username);

    bool _debug = false;

private:
    String m_host;
    String m_ApiKey;
    void addToBuffer(char c);
    void processBuffer() ;
    int processRequest(String username, String ApiEndpoint, String SearchFor);
};

#endif
