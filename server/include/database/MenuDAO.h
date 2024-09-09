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

class MenuDAO
{
public:
    MenuDAO();
    std::vector<Menu> fetchMenusWithFeedback();
    std::vector<Menu> fetchMenus();
    void fetchFeedbacks(Menu &menu);
    bool addMenu(const MenuAttributes &menu);
    bool deleteMenu(int menuId);
    bool insertDailyMenuEntries(const std::vector<DailyMenuEntry> &dailyMenuEntry);
    std::vector<DailyMenuAttributes> getDailyMenu();
    int getMenuIdFromDailyMenuId(int dailyMenuId);
    std::vector<DailyMenuAttributes> getDailyMenuWithAttributes();
    bool setDailyMenuAvailabilityToZero(int dailyMenuId);
    std::vector<FeedbackAnswer> fetchSuggestionsForMenu(int menuId);

private:
    std::shared_ptr<DatabaseConnection> dbConnection;
    std::shared_ptr<sql::Connection> connection;
};