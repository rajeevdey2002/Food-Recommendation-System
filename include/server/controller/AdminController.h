#pragma once

#include <functional>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <unordered_map>
#include "Sockets/TcpSocket.h"

#include "IController.h"
#include "server/service/FoodItemService.h"
#include "server/service/UserService.h"
namespace Controller {

class AdminController : public IController {

  std::shared_ptr<Service::UserService> userService;
  std::shared_ptr<Service::FoodItemService> foodItemService;

  std::string baseAuthEndpoint;
  std::unordered_map<
      std::string,
      std::function<bool(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                         rapidjson::Document &payload)>>
      authRoutes;

  bool addFoodItem(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                   rapidjson::Document &payload);
  bool removeFoodItem(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                      rapidjson::Document &payload);
  bool updateFoodItem(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                      rapidjson::Document &payload);
  bool getFoodItems(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                    rapidjson::Document &payload);
  bool addUser(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
               rapidjson::Document &payload);
  bool viewNotifications(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                         rapidjson::Document &payload);
  bool addFoodItemAttribute(std::shared_ptr<TcpSocket> socket,
                            rapidjson::Document request,
                            rapidjson::Document &payload);
  bool getAllAttributes(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                        rapidjson::Document &payload);
  bool viewFoodItemAttributes(std::shared_ptr<TcpSocket> socket,
                              rapidjson::Document request,
                              rapidjson::Document &payload);
  bool removeAttribute(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                       rapidjson::Document &payload);
  bool addAttribute(std::shared_ptr<TcpSocket> socket, rapidjson::Document request,
                    rapidjson::Document &payload);

public:
  AdminController(const std::string &authEndpoint,
                  std::shared_ptr<Service::UserService> userService,
                  std::shared_ptr<Service::FoodItemService> foodItemService);
  bool handleRequest(TcpSocket socket, rapidjson::Document request,
                     rapidjson::Document &payload) override;
  std::string getEndpoint() override;
};

}; // namespace Controller