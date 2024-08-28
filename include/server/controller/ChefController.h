#pragma once

#include <functional>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "AdminController.h"
#include "Sockets/TcpSocket.h"

#include "Functionalities/Actions.h"
#include "IController.h"
#include "server/service/FoodItemService.h"
#include "server/service/MenuService.h"
#include "server/service/RecommendationService.h"
#include "server/service/UserService.h"

namespace Controller {

class ChefController : public IController {

  std::shared_ptr<Service::UserService> userService;
  std::shared_ptr<Service::FoodItemService> foodItemService;
  std::shared_ptr<Service::MenuService> menuService;
  std::shared_ptr<Service::RecommendationService> recommendationService;

  std::unordered_map<
      ChefActions,
      std::function<bool(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                         rapidjson::Document &payload)>>
      actions;
  void registerActions();

  bool getRecommendedMenu(std::shared_ptr<TcpSocket> socket,
                          rapidjson::Document &request,
                          rapidjson::Document &payload);
  bool rolloutMenu(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                   rapidjson::Document &payload);
  bool createMenu(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                  rapidjson::Document &payload);
  bool viewRolloutMenu(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                       rapidjson::Document &payload);
  bool viewMenu(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                rapidjson::Document &payload);
  bool updateMenu(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                  rapidjson::Document &payload);
  bool viewRolloutFeedback(std::shared_ptr<TcpSocket> socket,
                           rapidjson::Document &request,
                           rapidjson::Document &payload);
  bool viewNotifications(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                         rapidjson::Document &payload);
  bool viewFoodItems(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                     rapidjson::Document &payload);

  bool addDiscardFeedbackQuestion(std::shared_ptr<TcpSocket> socket,
                                  rapidjson::Document &request,
                                  rapidjson::Document &payload);
  bool discardFoodItem(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                       rapidjson::Document &payload);
  bool viewDiscardFeedbackAnswerSentiments(std::shared_ptr<TcpSocket> socket,
                                           rapidjson::Document &request,
                                           rapidjson::Document &payload);
  bool viewDiscardFeedbackQuestions(std::shared_ptr<TcpSocket> socket,
                                    rapidjson::Document &request,
                                    rapidjson::Document &payload);
  bool getFoodItemsBelowRating(std::shared_ptr<TcpSocket> socket,
                               rapidjson::Document &request,
                               rapidjson::Document &payload);
  bool getDiscardedFoodItems(std::shared_ptr<TcpSocket> socket,
                             rapidjson::Document &request,
                             rapidjson::Document &payload);

public:
  ChefController(
      std::shared_ptr<Service::UserService> userService,
      std::shared_ptr<Service::FoodItemService> foodItemService,
      std::shared_ptr<Service::MenuService> menuService,
      std::shared_ptr<Service::RecommendationService> recommendationService);
  bool handleRequest(TcpSocket socket, rapidjson::Document &request,
                     rapidjson::Document &payload) override;
};

}; // namespace Controller