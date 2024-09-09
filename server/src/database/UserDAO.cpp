#include "../../include/database/UserDAO.h"
#include "DatabaseConnection.h"

UserDAO::UserDAO()
{
    dbConnection = DatabaseConnection::getInstance();
    connection = dbConnection->getConnection();
}

std::string UserDAO::authenticateUser(int userId, const std::string &password)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(connection->prepareStatement(
            "SELECT role FROM users WHERE userId = ? AND password = ?"));
        preparedStatement->setInt(1, userId);
        preparedStatement->setString(2, password);
        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        if (resultSet->next())
        {
            std::string role = resultSet->getString("role");
            return "STATUS_OK," + role;
        }
    }
    catch (sql::SQLException &e)
    {
        printf("UserDAO::authenticateUser() SQLException: %s\n", e.what());
    }
    return "ATHENTICATION_FAILURE";
}

bool UserDAO::addUser(const User &user)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(connection->prepareStatement("INSERT INTO users (userId, name, role, password) VALUES (?, ?, ?, ?)"));
        preparedStatement->setInt(1, user.userId);
        preparedStatement->setString(2, user.username);
        preparedStatement->setString(3, user.role);
        preparedStatement->setString(4, user.password);

        int rowsAffected = preparedStatement->executeUpdate();

        return rowsAffected == 1;
    }
    catch (sql::SQLException &e)
    {
        printf("UserDAO::addUser() SQLException: %s\n", e.what());
    }

    return false;
}

bool UserDAO::deleteUser(int userId)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(connection->prepareStatement("DELETE FROM users WHERE userId = ?"));
        preparedStatement->setInt(1, userId);

        int rowsAffected = preparedStatement->executeUpdate();

        return rowsAffected == 1;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "UserDAO::deleteUser() SQLException: " << e.what() << "\n";
    }

    return false;
}

bool UserDAO::insertUserOrderEntries(const std::vector<UserOrderEntry> &userOrderEntries)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("INSERT INTO userOrder (userId, dailyMenuId) VALUES (?, ?)"));

        for (const auto &entry : userOrderEntries)
        {
            preparedStatement->setInt(1, entry.userId);
            preparedStatement->setInt(2, entry.dailyMenuId);
            preparedStatement->executeUpdate();
        }

        return true;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "UserDAO::insertUserOrderEntries() SQLException: " << e.what() << "\n";
    }

    return false;
}

std::vector<Notification> UserDAO::getNonViewedNotificationsForUser(int userId)
{
    std::vector<Notification> notifications;

    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement(
                "SELECT n.notificationId, n.message, n.dateUpdated "
                "FROM notification n "
                "JOIN userNotificationStatus uvs ON n.notificationId = uvs.notificationId "
                "WHERE uvs.userId = ? AND uvs.viewedStatus = 'not_viewed'"));
        preparedStatement->setInt(1, userId);

        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        while (resultSet->next())
        {
            Notification notification;
            notification.notificationId = resultSet->getInt("notificationId");
            notification.message = resultSet->getString("message");
            notification.dateUpdated = resultSet->getString("dateUpdated");
            notifications.push_back(notification);
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "UserDAO::getNonViewedNotificationsForUser() SQLException: " << e.what() << "\n";
    }

    return notifications;
}

UserProfile UserDAO::fetchUserProfile(int userId)
{
    UserProfile profile;
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(connection->prepareStatement(
            "SELECT preferenceType, spiceLevel, cuisinePreference, sweetTooth FROM users WHERE userId = ?"));
        preparedStatement->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        if (resultSet->next())
        {
            profile.userId = userId;
            profile.preferenceType = resultSet->getString("preferenceType");
            profile.spiceLevel = resultSet->getString("spiceLevel");
            profile.cuisinePreference = resultSet->getString("cuisinePreference");
            profile.sweetTooth = resultSet->getString("sweetTooth");
        }
    }
    catch (sql::SQLException &e)
    {
        printf("UserDAO::fetchUserProfile() SQLException: %s\n", e.what());
    }
    return profile;
}

UserProfile UserDAO::getUserProfile(int userId)
{
    UserProfile userProfile;

    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement(
                "SELECT userId, preferenceType, spiceLevel, cuisinePreference, sweetTooth FROM users WHERE userId = ?"));

        preparedStatement->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        if (resultSet->next())
        {
            userProfile.userId = resultSet->getInt("userId");
            userProfile.preferenceType = resultSet->getString("preferenceType");
            userProfile.spiceLevel = resultSet->getString("spiceLevel");
            userProfile.cuisinePreference = resultSet->getString("cuisinePreference");
            userProfile.sweetTooth = resultSet->getString("sweetTooth");
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "UserDAO::getUserProfile() SQLException: " << e.what() << "\n";
    }

    return userProfile;
}

bool UserDAO::updateUserProfile(const UserProfile &profile)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement(
                "UPDATE users SET preferenceType = ?, spiceLevel = ?, cuisinePreference = ?, sweetTooth = ? WHERE userId = ?"));

        preparedStatement->setString(1, profile.preferenceType);
        preparedStatement->setString(2, profile.spiceLevel);
        preparedStatement->setString(3, profile.cuisinePreference);
        preparedStatement->setString(4, profile.sweetTooth);
        preparedStatement->setInt(5, profile.userId);

        int updatedRows = preparedStatement->executeUpdate();
        return updatedRows > 0;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "DatabaseController::updateUserProfile() SQLException: " << e.what() << "\n";
        return false;
    }
}