#include "../../include/database/MenuDAO.h"
#include "DatabaseConnection.h"

MenuDAO::MenuDAO()
{
    dbConnection = DatabaseConnection::getInstance();
    connection = dbConnection->getConnection();
}

std::vector<Menu> MenuDAO::fetchMenus()
{
    std::vector<Menu> menus;
    try
    {
        std::unique_ptr<sql::Statement> statement(connection->createStatement());
        std::unique_ptr<sql::ResultSet> resultSet(statement->executeQuery("SELECT menuId, menu_name, price FROM menu"));

        while (resultSet->next())
        {
            Menu menu;
            menu.menuId = resultSet->getInt("menuId");
            menu.menuName = resultSet->getString("menu_name");
            menu.price = resultSet->getDouble("price");
            menus.push_back(menu);
        }
    }
    catch (sql::SQLException &e)
    {
        printf("MenuDAO::fetchMenus() SQLException: %s\n", e.what());
    }

    return menus;
}

std::vector<Menu> MenuDAO::fetchMenusWithFeedback()
{
    std::vector<Menu> menus = fetchMenus();

    for (Menu &menu : menus)
    {
        fetchFeedbacks(menu);
    }

    return menus;
}

void MenuDAO::fetchFeedbacks(Menu &menu)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(connection->prepareStatement("SELECT feedback_Id, menuId, userId, rating, comment, feedback_date FROM feedback WHERE menuId = ?"));
        preparedStatement->setInt(1, menu.menuId);
        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        while (resultSet->next())
        {
            Feedback feedback;
            feedback.feedbackId = resultSet->getInt("feedback_Id");
            feedback.menuId = resultSet->getInt("menuId");
            feedback.userId = resultSet->getInt("userId");
            feedback.rating = resultSet->getDouble("rating");
            feedback.comment = resultSet->getString("comment");
            feedback.feedbackDate = resultSet->getString("feedback_date");
            menu.feedbacks.push_back(feedback);
        }
    }
    catch (sql::SQLException &e)
    {
        printf("MenuDAO::fetchFeedbacks() SQLException: %s\n", e.what());
    }
}

bool MenuDAO::addMenu(const MenuAttributes &menuData)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement(
                "INSERT INTO menu (menu_name, price, diet_type, spice_level, cuisine_type, sweet_type) VALUES (?, ?, ?, ?, ?, ?)"));

        preparedStatement->setString(1, menuData.menuName);
        preparedStatement->setDouble(2, menuData.price);
        preparedStatement->setString(3, menuData.dietType);
        preparedStatement->setString(4, menuData.spiceLevel);
        preparedStatement->setString(5, menuData.cuisineType);
        preparedStatement->setString(6, menuData.sweetType);

        int rowsAffected = preparedStatement->executeUpdate();
        return rowsAffected == 1;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "MenuDAO::addMenu() SQLException: " << e.what() << "\n";
    }

    return false;
}

bool MenuDAO::deleteMenu(int menuId)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("DELETE FROM menu WHERE menuId = ?"));
        preparedStatement->setInt(1, menuId);

        int rowsAffected = preparedStatement->executeUpdate();
        return rowsAffected == 1;
    }
    catch (sql::SQLException &e)
    {
        printf("MenuDAO::deleteMenu() SQLException: %s\n", e.what());
    }

    return false;
}

bool MenuDAO::insertDailyMenuEntries(const std::vector<DailyMenuEntry> &dailyMenuEntry)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("INSERT INTO dailyMenu (menuId, availability, mealCategory, menuDate) VALUES (?, ?, ?, CURDATE())"));

        for (const auto &entry : dailyMenuEntry)
        {
            preparedStatement->setInt(1, entry.menuId);
            preparedStatement->setInt(2, entry.availability);
            preparedStatement->setString(3, entry.mealCategory);
            preparedStatement->executeUpdate();
        }

        return true;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "MenuDAO::insertDailyMenuEntries() SQLException: " << e.what() << "\n";
    }

    return false;
}

std::vector<DailyMenuAttributes> MenuDAO::getDailyMenu()
{
    std::vector<DailyMenuAttributes> dailyMenu;

    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement(
                "SELECT dm.dailyMenuId, m.menu_name AS itemName, dm.availability, dm.mealCategory, m.price "
                "FROM dailyMenu dm "
                "JOIN menu m ON dm.menuId = m.menuId "
                "WHERE dm.menuDate = CURDATE()"));

        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        while (resultSet->next())
        {
            DailyMenuAttributes entry;
            entry.dailyMenuId = resultSet->getInt("dailyMenuId");
            entry.itemName = resultSet->getString("itemName");
            entry.availability = resultSet->getInt("availability");
            entry.mealCategory = resultSet->getString("mealCategory");
            entry.price = resultSet->getDouble("price");
            dailyMenu.push_back(entry);
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "MenuDAO::getDailyMenu() SQLException: " << e.what() << "\n";
    }

    return dailyMenu;
}

int MenuDAO::getMenuIdFromDailyMenuId(int dailyMenuId)
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
        std::cerr << "MenuDAO::getMenuIdFromDailyMenuId() SQLException: " << e.what() << "\n";
    }

    return -1;
}

std::vector<DailyMenuAttributes> MenuDAO::getDailyMenuWithAttributes()
{
    std::vector<DailyMenuAttributes> dailyMenu;

    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement(
                "SELECT dm.dailyMenuId, m.menu_name, dm.availability, dm.mealCategory, m.price, "
                "m.diet_type, m.spice_level, m.cuisine_type, m.sweet_type "
                "FROM dailyMenu dm "
                "JOIN menu m ON dm.menuId = m.menuId "
                "WHERE dm.menuDate = CURDATE()"));

        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        while (resultSet->next())
        {
            DailyMenuAttributes entry;
            entry.dailyMenuId = resultSet->getInt("dailyMenuId");
            entry.menuName = resultSet->getString("menu_name");
            entry.availability = resultSet->getInt("availability");
            entry.mealCategory = resultSet->getString("mealCategory");
            entry.price = resultSet->getDouble("price");
            entry.dietType = resultSet->getString("diet_type");
            entry.spiceLevel = resultSet->getString("spice_level");
            entry.cuisineType = resultSet->getString("cuisine_type");
            entry.sweetType = resultSet->getString("sweet_type");

            dailyMenu.push_back(entry);
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "MenuDAO::getDailyMenuWithAttributes() SQLException: " << e.what() << "\n";
    }

    return dailyMenu;
}

bool MenuDAO::setDailyMenuAvailabilityToZero(int dailyMenuId)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("UPDATE dailyMenu SET availability = 0 WHERE dailyMenuId = ?"));

        preparedStatement->setInt(1, dailyMenuId);
        preparedStatement->executeUpdate();

        return true;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "MenuDAO::setDailyMenuAvailabilityToZero() SQLException: " << e.what() << "\n";
    }

    return false;
}

std::vector<FeedbackAnswer> MenuDAO::fetchSuggestionsForMenu(int menuId)
{
    std::vector<FeedbackAnswer> feedbackAnswers;
    try
    {
        std::unique_ptr<sql::PreparedStatement> preparedStatement(
            connection->prepareStatement("SELECT question_id, answer_text, userId FROM FeedbackAnswer WHERE menuId = ?"));
        preparedStatement->setInt(1, menuId);

        std::unique_ptr<sql::ResultSet> resultSet(preparedStatement->executeQuery());

        while (resultSet->next())
        {
            FeedbackAnswer answer;
            answer.questionId = resultSet->getInt("question_id");
            answer.answerText = resultSet->getString("answer_text");
            answer.employeeId = resultSet->getInt("userId");

            feedbackAnswers.push_back(answer);
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "MenuDAO::fetchFeedbackAnswersForMenu() SQLException: " << e.what() << "\n";
    }

    return feedbackAnswers;
}