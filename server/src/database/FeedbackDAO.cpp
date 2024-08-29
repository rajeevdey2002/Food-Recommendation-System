#include "../../include/database/FeedbackDAO.h"
#include "DatabaseConnection.h"

FeedbackDAO::FeedbackDAO()
{
    dbConnection = DatabaseConnection::getInstance();
    connection = dbConnection->getConnection();
}

int FeedbackDAO::getMenuIdFromDailyMenuId(int dailyMenuId)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("SELECT menuId FROM dailyMenu WHERE dailyMenuId = ?"));
        preparedStatement->setInt(1, dailyMenuId);

        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        if (resultSet->next())
        {
            return resultSet->getInt("menuId");
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "FeedbackDAO::getMenuIdFromDailyMenuId() SQLException: " << e.what() << "\n";
    }

    return -1;
}

bool FeedbackDAO::insertUserFeedback(const Feedback &feedback)
{
    int menuId = getMenuIdFromDailyMenuId(feedback.menuId);
    if (menuId == -1)
    {
        std::cerr << "FeedbackDAO::insertUserFeedback() Error: Invalid dailyMenuId\n";
        return false;
    }

    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement(
                "INSERT INTO feedback (menuId, userId, rating, comment, feedback_date) VALUES (?, ?, ?, ?, CURDATE())"));

        preparedStatement->setInt(1, menuId);
        preparedStatement->setInt(2, feedback.userId);
        preparedStatement->setDouble(3, feedback.rating);
        preparedStatement->setString(4, feedback.comment);

        int rowsAffected = preparedStatement->executeUpdate();
        return rowsAffected == 1;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "FeedbackDAO::insertUserFeedback() SQLException (Insert feedback): " << e.what() << "\n";
    }

    return false;
}

bool FeedbackDAO::addFeedbackQuestion(const std::string &questionText)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("INSERT INTO FeedbackQuestion (question_text) VALUES (?)"));

        preparedStatement->setString(1, questionText);
        preparedStatement->executeUpdate();

        return true;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "FeedbackDAO::addFeedbackQuestion() SQLException: " << e.what() << "\n";
    }

    return false;
}

std::vector<std::pair<int, std::string>> FeedbackDAO::fetchFeedbackQuestions()
{
    std::vector<std::pair<int, std::string>> questions;
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("SELECT question_id, question_text FROM FeedbackQuestion"));

        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        while (resultSet->next())
        {
            int questionId = resultSet->getInt("question_id");
            std::string questionText = resultSet->getString("question_text");
            questions.emplace_back(questionId, questionText);
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "FeedbackDAO::fetchFeedbackQuestions() SQLException: " << e.what() << "\n";
    }

    return questions;
}

bool FeedbackDAO::storeFeedbackAnswers(const std::vector<FeedbackAnswer> &feedbackAnswers)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> getMenuIdStatement(
            connection->prepareStatement("SELECT menuId FROM dailyMenu WHERE dailyMenuId = ?"));

        std::unique_ptr<sql::PreparedStatement> insertFeedbackStatement(
            connection->prepareStatement("INSERT INTO FeedbackAnswer (question_id, menuId, userId, answer_text) VALUES (?, ?, ?, ?)"));

        for (const auto &answer : feedbackAnswers)
        {
            getMenuIdStatement->setInt(1, answer.foodId);
            std::unique_ptr<sql::ResultSet> resultSet(getMenuIdStatement->executeQuery());

            if (resultSet->next())
            {
                int menuId = resultSet->getInt("menuId");

                insertFeedbackStatement->setInt(1, answer.questionId);
                insertFeedbackStatement->setInt(2, menuId);
                insertFeedbackStatement->setInt(3, answer.employeeId);
                insertFeedbackStatement->setString(4, answer.answerText);
                insertFeedbackStatement->executeUpdate();
            }
            else
            {
                std::cerr << "FeedbackDAO::storeFeedbackAnswers() Error: Invalid dailyMenuId " << answer.foodId << "\n";
                return false;
            }
        }

        return true;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "FeedbackDAO::storeFeedbackAnswers() SQLException: " << e.what() << "\n";
    }

    return false;
}