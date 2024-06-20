#include "Client.h"
#include <iostream>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#endif

void Client::startClient(const char* serverIp, int port) {
    #ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }
    #endif

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIp, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return;
    }

    std::string message = "Hello from client";
    send(sock, message.c_str(), message.length(), 0);
    std::cout << "Message sent to server" << std::endl;

    recv(sock, buffer, 1024, 0);
    std::cout << "Response from server: " << buffer << std::endl;

    #ifdef _WIN32
    closesocket(sock);
    WSACleanup();
    #else
    close(sock);
    #endif
}
