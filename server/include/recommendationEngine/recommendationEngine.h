#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H

#include "IRecommendationEngine.h"
#include "MenuDAO.h"
#include "UserDAO.h"

#include <memory>

class RecommendationEngine : public IRecommendationEngine
{
public:
    RecommendationEngine(std::shared_ptr<UserDAO> userDAO, std::shared_ptr<MenuDAO> menuDAO) : userDAO(userDAO), menuDAO(menuDAO) {}
    std::vector<RecommendedMenuData> getRecommendedFood() override;
    std::vector<DailyMenuAttributes> getRecommendedFoodForUser(int userId) override;
    float calculateSentimentScore(const std::string &feedback);
    std::vector<DailyMenuAttributes> sortMenusByUserProfile(const std::vector<DailyMenuAttributes> &menus, const UserProfile &profile);
    std::vector<Menu> getDiscardedFood() override;

private:
    std::shared_ptr<UserDAO> userDAO;
    std::shared_ptr<MenuDAO> menuDAO;
};

#endif