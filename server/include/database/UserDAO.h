#pragma once

#include "DatabaseConnection.h"
#include "Utils.h"
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


class UserDAO
{
public:
    UserDAO();
    std::string authenticateUser(int userId, const std::string &password);
    bool addUser(const User &user);
    bool deleteUser(int userId);
    bool insertUserOrderEntries(const std::vector<UserOrderEntry> &userOrderEntries);
    std::vector<Notification> getNonViewedNotificationsForUser(int userId);
    UserProfile fetchUserProfile(int userId);
    UserProfile getUserProfile(int userId);
    bool updateUserProfile(const UserProfile &profile);

private:
    std::shared_ptr<DatabaseConnection> dbConnection;
    std::shared_ptr<sql::Connection> connection;
};