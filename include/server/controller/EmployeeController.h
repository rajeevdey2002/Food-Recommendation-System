#pragma once

#include <functional>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "Sockets/TcpSocket.h"

#include "Functionalities/Actions.h"
#include "IController.h"
#include "server/service/FoodItemService.h"
#include "server/service/MenuService.h"
#include "server/service/RecommendationService.h"
#include "server/service/UserService.h"

namespace Controller {

class EmployeeController : public IController {

  std::shared_ptr<Service::UserService> userService;
  std::shared_ptr<Service::FoodItemService> foodItemService;
  std::shared_ptr<Service::MenuService> menuService;
  std::shared_ptr<Service::RecommendationService> recommendationService;

  std::unordered_map<
      EmployeeActions,
      std::function<bool(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                         rapidjson::Document &payload)>>
      actions;

  bool viewMenu(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                rapidjson::Document &payload);
  bool viewMenuRollout(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                       rapidjson::Document &payload);
  bool sendFeedback(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                    rapidjson::Document &payload);
  bool viewNotifications(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                         rapidjson::Document &payload);
  bool writeReview(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                   rapidjson::Document &payload);
  bool getAttributes(std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
                     rapidjson::Document &payload);
  bool viewFoodItemAttributes(std::shared_ptr<TcpSocket> socket,
                              rapidjson::Document &request,
                              rapidjson::Document &payload);
  bool addFoodPreferences(std::shared_ptr<TcpSocket> socket,
                          rapidjson::Document &request,
                          rapidjson::Document &payload);
  bool deleteFoodPreferences(std::shared_ptr<TcpSocket> socket,
                             rapidjson::Document &request,
                             rapidjson::Document &payload);
  bool getFoodPreferences(std::shared_ptr<TcpSocket> socket,
                          rapidjson::Document &request,
                          rapidjson::Document &payload);
  bool getDiscardedFoodItems(std::shared_ptr<TcpSocket> socket,
                             rapidjson::Document &request,
                             rapidjson::Document &payload);
  bool getDiscardedFoodItemQuestions(std::shared_ptr<TcpSocket> socket,
                                     rapidjson::Document &request,
                                     rapidjson::Document &payload);
  bool addDiscardedFoodItemAnswer(std::shared_ptr<TcpSocket> socket,
                                  rapidjson::Document &request,
                                  rapidjson::Document &payload);
  void sortFoodItems(uint64_t userId,
                     std::vector<Service::FoodItem> &foodItems);

public:
  EmployeeController(
      std::shared_ptr<Service::UserService> userService,
      std::shared_ptr<Service::FoodItemService> foodItemService,
      std::shared_ptr<Service::MenuService> menuService,
      std::shared_ptr<Service::RecommendationService> recommendationService);
  bool handleRequest(TcpSocket socket, rapidjson::Document &request,
                     rapidjson::Document &payload) override;
};

}; // namespace Controller