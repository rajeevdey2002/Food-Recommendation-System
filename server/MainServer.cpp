#include "include/recommendationEngine/RecommendationEngine.h"
#include "include/requestHandler/RequestHandler.h"
#include "include/serverHandler/ServerHandler.h"
#include "include/database/DatabaseConnection.h"
#include "FeedbackDAO.h"
#include "NotificationDAO.h"
#include <memory>


int main()
{
    DatabaseConnection::initDatabaseConnection("tcp://127.0.0.1", "root", "E2developer@Dune", "recommendationEngine");
    std::shared_ptr<UserDAO> userDAO = std::make_shared<UserDAO>();
    std::shared_ptr<MenuDAO> menuDAO = std::make_shared<MenuDAO>();
    std::shared_ptr<NotificationDAO> notificationDAO = std::make_shared<NotificationDAO>();
    std::shared_ptr<FeedbackDAO> feedbackDAO = std::make_shared<FeedbackDAO>();
    std::shared_ptr<IRecommendationEngine> recommendationEngine = std::make_shared<RecommendationEngine>(userDAO, menuDAO);
    std::shared_ptr<IRequestHandler> requestHandler = std::make_shared<RequestHandler>(userDAO, menuDAO, notificationDAO, feedbackDAO, recommendationEngine);
    std::shared_ptr<serverHandler> server = std::make_shared<serverHandler>(1234, requestHandler);

    server->start();

    return 0;
}