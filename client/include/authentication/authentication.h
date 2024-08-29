#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "../serverConnection/serverConnection.h"
#include "../clientUtilities/userInputHandler.h"

class Authentication
{
public:
    Authentication(ServerConnection &serverConn);

    std::string authenticateUser(int userId, const std::string &password);

private:
    ServerConnection &serverConn;
};

#endif
