#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "../database/FeedbackDAO.h"
#include "IRequestHandler.h"
#include "../recommendationEngine/IRecommendationEngine.h"
#include "../serverUtilities/ServerDataParser.h"
#include "../database/MenuDAO.h"
#include "NotificationDAO.h"
#include "UserDAO.h"
#include <memory>

class RequestHandler : public IRequestHandler
{
public:
  RequestHandler(std::shared_ptr<UserDAO> userDAO,
                 std::shared_ptr<MenuDAO> menuDAO,
                 std::shared_ptr<NotificationDAO> notificationDAO,
                 std::shared_ptr<FeedbackDAO> feedbackDAO,
                 std::shared_ptr<IRecommendationEngine> recommendationEngine);
  void handleRequest(int new_socket) override;

private:
    std::shared_ptr<UserDAO> userDAO;
    std::shared_ptr<MenuDAO> menuDAO;
    std::shared_ptr<NotificationDAO> notificationDAO;
    std::shared_ptr<FeedbackDAO> feedbackDAO;
    std::shared_ptr<IRecommendationEngine> recommendationEngine;
    std::shared_ptr<DataParser> dataParser;

    std::string readFromSocket(int new_socket);
    std::string processRequest(const GeneralRequest &request);
    std::string handleLoginRequest(const std::string &data);
    std::string handleGetRecommendedFoodRequest();
    std::string handleAddUserRequest(const std::string &data);
    std::string handleDelUserRequest(const std::string &data);
    std::string handleAddMenuRequest(const std::string &data);
    std::string handleDelMenuRequest(const std::string &data);
    std::string handleAddDailyMenuItemRequest(const std::string &data);
    std::string handleGetDailyMenuRequest(const std::string &data);
    std::string handlePlaceOrderRequest(const std::string &data);
    std::string handleAddUserFeedbackRequest(const std::string &data);
    std::string handleNotification(const std::string &data);
    std::string handleGetNotifications(const std::string &data);
    std::string handleMarkNotificationsViewed(const std::string &data);
    std::string handleUpdateProfile(const std::string &data);
    std::string handleViewProfile(const std::string &data);
    std::string handleSetDailyMenuAvailabilityToZeroRequest(const std::string &data);
    std::string handleFetchFeedback(const std::string &data);
    std::string handleAddFeedbackQuestion(const std::string &data);
    std::string handleFetchFeedbackQuestions();
    std::string handleUpdateFeedbackAnswer(const std::string &data);
    std::string handlefetchSuggestionForMenu(const std::string &data);
    std::string handleGetDiscardedMenu();
};

#endif
