#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <stdexcept>
#include <memory>

class DatabaseConnection {
public:
    static DatabaseConnection* getInstance();
    sql::Connection* getConnection();
    ~DatabaseConnection();

private:
    DatabaseConnection();
    static std::unique_ptr<DatabaseConnection> instance;
    std::unique_ptr<sql::Connection> connection;

    const char* host;
    const char* user;
    const char* password;
    const char* database;
};

#endif // DATABASE_CONNECTION_H
