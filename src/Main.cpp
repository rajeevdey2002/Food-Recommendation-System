#include "Client.h"
#include "Server.h"
#include "DatabaseConnection.h"
#include "service/LoginService.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <string>

std::atomic<bool> serverRunning(true);

void stopServer() {
    std::cout << "Stopping server..." << std::endl;
    serverRunning = false;
}

void startClientInterface() {
    std::string serverIp;
    int port;
    std::cout << "Enter server IP: ";
    std::cin >> serverIp;
    std::cout << "Enter port number: ";
    std::cin >> port;
    std::cin.ignore();
    Client::startClient(serverIp.c_str(), port);
}

void startServerInterface(int port) {
    std::thread serverThread(Server::startServer, port);

    std::string command;
    while (serverRunning) {
        std::cin >> command;
        if (command == "exit") {
            Server::stopServer();
            break;
        }
    }

    if (serverThread.joinable()) {
        serverThread.join();
    }
}

void testDatabaseConnection() {
    try {
        auto db = DatabaseConnection::getInstance();
        auto conn = db->getConnection();
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT 1"));
        
        if (res->next()) {
            std::cout << "Database connection is working correctly." << std::endl;
        } else {
            std::cout << "Failed to retrieve test query result." << std::endl;
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error connecting to the database: " << e.what() << std::endl;
    }
}

void handleLogin() {
    uint64_t userId;
    std::string password;
    std::cout << "Enter user ID: ";
    std::cin >> userId;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (Service::LoginService::loginUser(userId, password)) {
        std::cout << "Login successful." << std::endl;
    } else {
        std::cout << "Invalid user ID or password." << std::endl;
    }
}

void handleLogout() {
    uint64_t loginId;
    std::cout << "Enter login ID: ";
    std::cin >> loginId;

    if (Service::LoginService::logoutUser(loginId)) {
        std::cout << "Logout successful." << std::endl;
    } else {
        std::cout << "Error during logout." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <s|c|t|l|o>\n";
        std::cerr << "s: Start server\n";
        std::cerr << "c: Start client\n";
        std::cerr << "t: Test database connection\n";
        std::cerr << "l: Login\n";
        std::cerr << "o: Logout\n";
        return 1;
    }

    char mode = argv[1][0];
    if (mode == 's') {
        int port = 8080;
        startServerInterface(port);
    } else {
        while (true) {
            std::cout << "Choose an action: (c) Start client, (t) Test database connection, (l) Login, (o) Logout, (e) Exit: ";
            char choice;
            std::cin >> choice;
            std::cin.ignore(); 

            if (choice == 'c') {
                startClientInterface();
            } else if (choice == 't') {
                testDatabaseConnection();
            } else if (choice == 'l') {
                handleLogin();
            } else if (choice == 'o') {
                handleLogout();
            } else if (choice == 'e') {
                std::cout << "Exiting program." << std::endl;
                break;
            } else {
                std::cerr << "Invalid choice. Please try again." << std::endl;
            }
        }
    }

    return 0;
}
