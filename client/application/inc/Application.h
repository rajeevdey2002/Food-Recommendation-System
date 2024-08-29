#ifndef APPLICATION_H
#define APPLICATION_H

#include "serverConnection.h"
#include "userInputHandler.h"
#include "authentication.h"
#include "chef.h"
#include "admin.h"
#include "employee.h"

class Application
{
public:
    void run();

private:
    void displayMainMenu() const;
    void handleUserSession(int choice, const std::string &role, int id, const std::string &password, ServerConnection &serverConnection) const;
    void handleAdminSession(const std::string &role, int id, const std::string &password, ServerConnection &serverConnection) const;
    void handleChefSession(const std::string &role, int id, const std::string &password, ServerConnection &serverConnection) const;
    void handleEmployeeSession(const std::string &role, int id, const std::string &password, ServerConnection &serverConnection) const;
    void handleServerConnectionFailure() const;
};

#endif
