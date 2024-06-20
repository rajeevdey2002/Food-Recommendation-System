#include "Server.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <string.h>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#endif

std::atomic<bool> Server::serverRunning(true);

void Server::initDatabase() {
    DatabaseConnection::getInstance();
}

std::vector<std::string> Server::getUserEmails() {
    std::vector<std::string> emails;
    auto db = DatabaseConnection::getInstance();
    auto conn = db->getConnection();
    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT email FROM Users"));

    while (res->next()) {
        emails.push_back(res->getString("email"));
    }
    return emails;
}

void Server::handleClient(int newSocket) {
    char buffer[1024] = {0};
    while (true) {
        int bytesRead = recv(newSocket, buffer, 1024, 0);
        if (bytesRead <= 0) break;

        std::cout << "Message from client: " << buffer << std::endl;

        std::string response;
        if (strcmp(buffer, "get_emails") == 0) {
            std::vector<std::string> emails = getUserEmails();
            response = "Emails: ";
            for (const auto& email : emails) {
                response += email + " ";
            }
        } else {
            response = "Unknown command";
        }

        send(newSocket, response.c_str(), response.length(), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    #ifdef _WIN32
    closesocket(newSocket);
    #else
    close(newSocket);
    #endif
}

void Server::startServer(int port) {
    #ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }
    #endif

    int serverFd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        #ifdef _WIN32
        closesocket(serverFd);
        WSACleanup();
        #else
        close(serverFd);
        #endif
        exit(EXIT_FAILURE);
    }

    if (listen(serverFd, 3) < 0) {
        perror("listen");
        #ifdef _WIN32
        closesocket(serverFd);
        WSACleanup();
        #else
        close(serverFd);
        #endif
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << std::endl;

    initDatabase(); // Initialize the database

    std::vector<std::thread> clientThreads;
    while (serverRunning) {
        int newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (newSocket < 0) {
            if (serverRunning) {
                perror("accept");
                continue;
            } else {
                break;
            }
        }
        clientThreads.push_back(std::thread(handleClient, newSocket));
    }

    for (auto& th : clientThreads) {
        if (th.joinable()) {
            th.join();
        }
    }

    #ifdef _WIN32
    closesocket(serverFd);
    WSACleanup();
    #else
    close(serverFd);
    #endif
}

void Server::stopServer() {
    serverRunning = false;
}
