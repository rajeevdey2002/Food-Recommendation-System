#include "../../include/database/NotificationDAO.h"
#include "DatabaseConnection.h"

NotificationDAO::NotificationDAO()
{
    dbConnection = DatabaseConnection::getInstance();
    connection = dbConnection->getConnection();
}

bool NotificationDAO::insertNotification(const std::string &message)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("INSERT INTO notification (message) VALUES (?)"));
        preparedStatement->setString(1, message);
        int rowsAffected = preparedStatement->executeUpdate();
        return rowsAffected == 1;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "NotificationDAO::insertNotification() SQLException: " << e.what() << "\n";
        return false;
    }
}

bool NotificationDAO::addNotification(const std::string &message)
{
    try
    {
        connection->setAutoCommit(false);

        std::unique_ptr<sql::PreparedStatement> insertNotificationStmt(
            connection->prepareStatement("INSERT INTO notification (message) VALUES (?)"));
        insertNotificationStmt->setString(1, message);
        insertNotificationStmt->executeUpdate();

        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT LAST_INSERT_ID() AS notificationId"));
        int notificationId;
        if (res->next())
        {
            notificationId = res->getInt("notificationId");
        }

        std::unique_ptr<sql::PreparedStatement> insertUserNotificationStatusStmt(
            connection->prepareStatement("INSERT INTO userNotificationStatus (userId, notificationId, viewedStatus) SELECT userId, ?, 'not_viewed' FROM users"));
        insertUserNotificationStatusStmt->setInt(1, notificationId);
        insertUserNotificationStatusStmt->executeUpdate();

        connection->commit();
        connection->setAutoCommit(true);

        return true;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "NotificationDAO::addNotification() SQLException: " << e.what() << "\n";
        connection->rollback();
        connection->setAutoCommit(true);
    }

    return false;
}

bool NotificationDAO::markNotificationsAsViewed(int userId, const std::vector<int> &notificationIds)
{
    printf("NotificationDAO::markNotificationsAsViewed entry ");
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement(
                "UPDATE userNotificationStatus SET viewedStatus = 'viewed' WHERE userId = ? AND notificationId = ?"));

        for (const int &notificationId : notificationIds)
        {
            preparedStatement->setInt(1, userId);
            preparedStatement->setInt(2, notificationId);
            preparedStatement->executeUpdate();
        }

        return true;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "NotificationDAO::markNotificationsAsViewed() SQLException: " << e.what() << "\n";
    }

    return false;
}