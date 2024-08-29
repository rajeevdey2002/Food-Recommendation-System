#include "../../include/database/databaseController.h"
#include "../../include/recommendationEngine/recommendationEngine.h"
#include "../../include/requestHandler/requestHandler.h"
#include "../../include/serverHandler/serverHandler.h"


int main()
{
    std::shared_ptr<IDatabaseController> database = std::make_shared<DatabaseController>();
    std::shared_ptr<IRecommendationEngine> recommendationEngine = std::make_shared<RecommendationEngine>(database);
    std::shared_ptr<IRequestHandler> requestHandler = std::make_shared<RequestHandler>(database, recommendationEngine);
    std::shared_ptr<serverHandler> server = std::make_shared<serverHandler>(1234, requestHandler);

    server->start();

    return 0;
}