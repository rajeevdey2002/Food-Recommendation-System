#pragma once

#include "DatabaseConnection.h"
#include "utils.h"
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class FeedbackDAO
{
public:
    FeedbackDAO();
    bool insertUserFeedback(const Feedback &feedback);
    bool addFeedbackQuestion(const std::string &questionText);
    std::vector<std::pair<int, std::string>> fetchFeedbackQuestions();
    bool storeFeedbackAnswers(const std::vector<FeedbackAnswer> &feedbackAnswers);
    int getMenuIdFromDailyMenuId(int dailyMenuId);

private:
    std::shared_ptr<DatabaseConnection> dbConnection;
    std::shared_ptr<sql::Connection> connection;
};