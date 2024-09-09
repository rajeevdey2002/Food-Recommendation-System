#pragma once

#include "DatabaseConnection.h"
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class NotificationDAO
{
public:
    NotificationDAO();
    bool insertNotification(const std::string &message);
    bool addNotification(const std::string &message);
    bool markNotificationsAsViewed(int userId, const std::vector<int> &notificationIds);

private:
    std::shared_ptr<DatabaseConnection> dbConnection;
    std::shared_ptr<sql::Connection> connection;
};