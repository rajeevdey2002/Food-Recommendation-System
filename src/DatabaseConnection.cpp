#include "DatabaseConnection.h"

std::unique_ptr<DatabaseConnection> DatabaseConnection::instance = nullptr;

DatabaseConnection::DatabaseConnection()
    : host("tcp://127.0.0.1:3306"), user("rajeev"), password("Workshop@2024"), database("tempDatabase") {
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    connection.reset(driver->connect(host, user, password));
    connection->setSchema(database);
}

DatabaseConnection* DatabaseConnection::getInstance() {
    if (instance == nullptr) {
        instance.reset(new DatabaseConnection());
    }
    return instance.get();
}

sql::Connection* DatabaseConnection::getConnection() {
    return connection.get();
}

DatabaseConnection::~DatabaseConnection() {
}
