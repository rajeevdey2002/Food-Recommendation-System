#include "Client.h"
#include "Server.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <thread>
#include <atomic>

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
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Users"));
        
        std::cout << "Users in the database:" << std::endl;
        while (res->next()) {
            std::cout << "ID: " << res->getInt("id") << ", Name: " << res->getString("name") << ", Email: " << res->getString("email") << std::endl;
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error connecting to the database: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <s|c|t>\n";
        std::cerr << "s: Start server\n";
        std::cerr << "c: Start client\n";
        std::cerr << "t: Test database connection\n";
        return 1;
    }

    char mode = argv[1][0];
    if (mode == 's') {
        int port = 8080; // or any port you prefer
        startServerInterface(port);
    } else if (mode == 'c') {
        startClientInterface();
    } else if (mode == 't') {
        testDatabaseConnection();
    } else {
        std::cerr << "Invalid argument. Use 's' for server, 'c' for client, or 't' to test the database connection.\n";
        return 1;
    }

    return 0;
}
