#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <string>
#include <vector>

class Server {
private:
    static std::atomic<bool> serverRunning;

public:
    static void startServer(int port);
    static void stopServer();
    static void handleClient(int newSocket);
    static void initDatabase();
    static std::vector<std::string> getUserEmails();
};

#endif
