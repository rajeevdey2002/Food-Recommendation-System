#ifndef DATABASECONTOLLER_H
#define DATABASECONTOLLER_H

#include "IDatabaseController.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include "IDatabaseController.h"

class DatabaseController : public IDatabaseController
{
public:
    DatabaseController(const std::string &dbHost = "tcp://127.0.0.1", const std::string &user = "root",
                       const std::string &password = "E2developer@Dune", const std::string &database = "recommendationEngine");
    std::vector<Menu> fetchMenusWithFeedback() override;
    std::vector<Menu> fetchMenus() override;
    void fetchFeedbacks(Menu &menu) override;
    std::string authenticateUser(int userId, const std::string &password) override;
    bool addUser(const User &user) override;
    bool deleteUser(int userId) override;
    bool addMenu(const MenuAttributes &menu) override;
    bool deleteMenu(int menuId) override;
    bool insertDailyMenuEntries(const std::vector<DailyMenuEntry> &dailyMenuEntry) override;
    std::vector<DailyMenuAttributes> getDailyMenu() override;
    bool insertUserOrderEntries(const std::vector<UserOrderEntry> &userOrderEntries) override;
    int getMenuIdFromDailyMenuId(int dailyMenuId);
    bool insertUserFeedback(const Feedback &feedback) override;
    bool insertNotification(const std::string &message) override;
    bool addNotification(const std::string &message) override;
    std::vector<Notification> getNonViewedNotificationsForUser(int userId) override;
    bool markNotificationsAsViewed(int userId, const std::vector<int> &notificationIds) override;
    UserProfile fetchUserProfile(int userId) override;
    std::vector<DailyMenuAttributes> getDailyMenuWithAttributes() override;
    bool updateUserProfile(const UserProfile &profile) override;
    UserProfile getUserProfile(int userId) override;
    bool setDailyMenuAvailabilityToZero(int dailyMenuId) override;
    bool addFeedbackQuestion(const std::string &questionText) override;
    std::vector<std::pair<int, std::string>> fetchFeedbackQuestions() override;
    bool storeFeedbackAnswers(const std::vector<FeedbackAnswer> &feedbackAnswers) override;
    std::vector<FeedbackAnswer> fetchSuggestionsForMenu(int menuId) override;

private:
    void connect();

    std::string dbHost;
    std::string user;
    std::string password;
    std::string database;
    std::unique_ptr<sql::Connection> connection;
};

#endif