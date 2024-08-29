#include "../../include/application/Application.h"
#include <iostream>
#include <unistd.h>

#define SERVER_PORT 1234
#define SERVER_IP "127.0.0.1"

void Application::run()
{
    ServerConnection serverConnection(SERVER_IP, SERVER_PORT);
    while (true)
    {
        if (!serverConnection.connectToServer())
        {
            handleServerConnectionFailure();
            continue;
        }
        UserInputHandler userInputHandler;
        Authentication auth(serverConnection);

        displayMainMenu();
        int choice = userInputHandler.getIntInput("\nSelect an option: ");
        if (choice == 4)
        {
            std::cout << "Exiting the application. Goodbye!\n";
            break;
        }

        int id = userInputHandler.getIntInput("Please enter your ID: ");
        std::string password = userInputHandler.getStringInput("Please enter your password: ");
        std::string role = auth.authenticateUser(id, password);

        handleUserSession(choice, role, id, password, serverConnection);
    }
}

void Application::displayMainMenu() const
{
    std::cout << "\033[1;32m" << R"(
   __________________________________________________
  |                                                  |
  |                  ITT Cafeteria                   |
  |__________________________________________________|
)" << "\033[0m" << std::endl;
    std::cout << "Main Menu:\n";
    std::cout << "1. Login as Admin\n";
    std::cout << "2. Login as Chef\n";
    std::cout << "3. Login as Employee\n";
    std::cout << "4. Exit the Application\n";
}

void Application::handleUserSession(int choice, const std::string &role, int id, const std::string &password, ServerConnection &serverConnection) const
{
    try
    {
        switch (choice)
        {
        case 1:
            handleAdminSession(role, id, password, serverConnection);
            break;
        case 2:
            handleChefSession(role, id, password, serverConnection);
            break;
        case 3:
            handleEmployeeSession(role, id, password, serverConnection);
            break;
        default:
            std::cout << "Invalid selection. Please choose a valid option from the menu.\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Application::handleAdminSession(const std::string &role, int id, const std::string &password, ServerConnection &serverConnection) const
{
    if (role == "ADMIN")
    {
        Admin admin(id, password, serverConnection);
        admin.mainMenu();
    }
    else
    {
        std::cout << "Authentication failed for Admin. Please check your credentials.\n";
    }
}

void Application::handleChefSession(const std::string &role, int id, const std::string &password, ServerConnection &serverConnection) const
{
    if (role == "CHEF")
    {
        Chef chef(id, password, serverConnection);
        chef.mainMenu();
    }
    else
    {
        std::cout << "Authentication failed for Chef. Please check your credentials.\n";
    }
}

void Application::handleEmployeeSession(const std::string &role, int id, const std::string &password, ServerConnection &serverConnection) const
{
    if (role == "EMPLOYEE")
    {
        Employee employee(id, password, serverConnection);
        employee.mainMenu();
    }
    else
    {
        std::cout << "Authentication failed for Employee. Please check your credentials.\n";
    }
}

void Application::handleServerConnectionFailure() const
{
    std::cout << "Unable to connect to server. Retrying in a moment..." << std::endl;
    sleep(2);
    system("clear");
}
