#include "server/controller/AdminController.h"
#include "Category.h"
#include "FoodItem.h"
#include "Functionalities/Actions.h"
#include "User.h"
#include <asm-generic/errno.h>
#include <cstdint>
#include <rapidjson/document.h>
#include <regex>
#include <sys/types.h>
#include <utility>

using Controller::AdminController;

AdminController::AdminController(
    std::shared_ptr<Service::UserService> userService,
    std::shared_ptr<Service::FoodItemService> foodItemService)
    : userService(userService),
      foodItemService(foodItemService) {
  actions.insert(
      {AdminActions::ADD_FOOD_ITEM,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->addFoodItem(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::REMOVE_FOOD_ITEM,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->removeFoodItem(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::UPDATE_FOOD_ITEM,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->updateFoodItem(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::GET_FOOD_ITEMS,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->getFoodItems(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::ADD_USER,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->addUser(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::VIEW_NOTIFICATIONS,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewNotifications(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::ADD_FOOD_ITEM_ATTRIBUTE,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->addFoodItemAttribute(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::GET_ALL_ATTRIBUTES,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->getAllAttributes(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::VIEW_FOOD_ITEM_ATTRIBUTES,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewFoodItemAttributes(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::REMOVE_ATTRIBUTE,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->removeAttribute(socket, request, payload);
       }});
  actions.insert(
      {AdminActions::ADD_ATTRIBUTE,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->addAttribute(socket, request, payload);
       }});
};

bool AdminController::handleRequest(TcpSocket socket,
                                    rapidjson::Document &request,
                                    rapidjson::Document &payload) {

  if (request.HasMember("action") && request["action"].IsInt()) {
    int action = request["action"].GetInt();
    if (actions.count((AdminActions)action) > 0)
    {
      std::shared_ptr<TcpSocket> socketPtr =
      std::make_shared<TcpSocket>(std::move(socket));
      return actions[(AdminActions)action](socketPtr, request, payload);
    }
  }
  return false;
}

bool AdminController::addFoodItem(std::shared_ptr<TcpSocket> socket,
                                  rapidjson::Document &request,
                                  rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  rapidjson::Document responsePayload;
  if (!responsePayload.IsObject()) {
        responsePayload.SetObject();
    }
  try {
    DTO::FoodItem foodItem = DTO::FoodItem::fromJson(payload);
    if (foodItemService->addFoodItem(foodItem)) {
      writeResponse(responseBuffer, request, 0, responsePayload);
    } else {
      std::string responseString{"Failed to add food item"};
      responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
      writeResponse(responseBuffer, request, 400, responsePayload);
    }
  } catch (std::exception &e) {
    std::cout << "Error adding food item: " << e.what() << std::endl;
    std::string responseString{"Failed to add food item due to : " +
                           std::string(e.what())};
      responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::removeFoodItem(std::shared_ptr<TcpSocket> socket,
                                     rapidjson::Document &request,
                                     rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  rapidjson::Document responsePayload;
  if (!responsePayload.IsObject()) {
        responsePayload.SetObject();
    }
  try {
    uint64_t foodItemId;
    if (payload.HasMember("foodItemId") && payload["foodItemId"].IsUint64())
    {
      foodItemId = payload["foodItemId"].GetUint64();
    }
    else {
      return false;
    }
    if (foodItemService->deleteFoodItem(foodItemId)) {
      writeResponse(responseBuffer, request, 0, responsePayload);
    } else {
      std::string responseString{"Failed to remove food item"};
      responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
      writeResponse(responseBuffer, request, 400, responsePayload);
    }
  } catch (std::exception &e) {
    std::cout << "Error removing food item: " << e.what() << std::endl;
    std::string responseString{"Failed to remove food item due to : " +
                           std::string(e.what())};
    responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::updateFoodItem(std::shared_ptr<TcpSocket> socket,
                                     rapidjson::Document &request,
                                     rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  rapidjson::Document responsePayload;
  if (!responsePayload.IsObject()) {
        responsePayload.SetObject();
    }
  try {
    DTO::FoodItem foodItem = DTO::FoodItem::fromJson(payload);
    if (foodItemService->updateFoodItem(foodItem)) {
      writeResponse(responseBuffer, request, 0, responsePayload);
    } else {
      std::string responseString{"Failed to update food item"};
      responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
      writeResponse(responseBuffer, request, 400, responsePayload);
    }
  } catch (std::exception &e) {
    std::cout << "Error updating food item: " << e.what() << std::endl;
    std::string responseString{"Failed to update food item due to : " +
                           std::string(e.what())};
    responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::getFoodItems(std::shared_ptr<TcpSocket> socket,
                                   rapidjson::Document &request,
                                   rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  rapidjson::Document responsePayload;
  if (!responsePayload.IsObject()) {
        responsePayload.SetObject();
    }
  try {
    uint64_t categoryId;
    if (payload.HasMember("categoryId") && payload["categoryId"].IsUint64())
    {
      categoryId = payload["categoryId"].GetUint64();
    }
    else {
      return false;
    }
    std::vector<DTO::FoodItem> foodItems =
        foodItemService->getFoodItemsByCategory(
            (DTO::Category)(uint64_t)categoryId);
    rapidjson::Value foodItemsArray(rapidjson::kArrayType);
        auto& allocator = responsePayload.GetAllocator();

        for (const auto& item : foodItems) {
            rapidjson::Document itemDoc;
            itemDoc.SetObject();
            item.toJson(itemDoc);
            rapidjson::Value itemValue;
            itemValue.CopyFrom(itemDoc, allocator);
            foodItemsArray.PushBack(itemValue, allocator);
        }
        responsePayload.AddMember("foodItems", foodItemsArray, allocator);
        writeResponse(responseBuffer, request, 0, responsePayload);
  } catch (std::exception &e) {
    std::cout << "Error getting food items: " << e.what() << std::endl;
    std::string responseString{"Failed to get food items due to : " +
                           std::string(e.what())};
    responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::addUser(std::shared_ptr<TcpSocket> socket,
                              rapidjson::Document &request,
                              rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  rapidjson::Document responsePayload;
  if (!responsePayload.IsObject()) {
        responsePayload.SetObject();
    }
  try {
    DTO::User user = DTO::User::fromJson(payload);
    if (userService->addUser(user)) {
      writeResponse(responseBuffer, request, 0, responsePayload);
    } else {
      std::string responseString{"Failed to add user"};
      responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
      writeResponse(responseBuffer, request, 400, responsePayload);
    }
  } catch (std::exception &e) {
    std::cout << "Error adding user: " << e.what() << std::endl;
    std::string responseString{"Failed to add user due to : " +
                           std::string(e.what())};
    responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::viewNotifications(std::shared_ptr<TcpSocket> socket,
                                        rapidjson::Document &request,
                                        rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  rapidjson::Document responsePayload;
  if (!responsePayload.IsObject()) {
        responsePayload.SetObject();
    }
  try {
    uint64_t userId;
    if (payload.HasMember("userId") && payload["userId"].IsUint64())
    {
      userId = payload["userId"].GetUint64();
    }
    else {
      return false;
    }
    std::vector<DTO::Notification> notifications =
        userService->getUnreadNotifications(userId);
    rapidjson::Value notificationsArray(rapidjson::kArrayType);
        auto& allocator = responsePayload.GetAllocator();

        for (const auto& notification : notifications) {
            rapidjson::Document itemDoc;
            itemDoc.SetObject();
            notification.toJson(itemDoc);
            rapidjson::Value itemValue;
            itemValue.CopyFrom(itemDoc, allocator);
            notificationsArray.PushBack(itemValue, allocator);
        }
        responsePayload.AddMember("notifications", notificationsArray, allocator);
        writeResponse(responseBuffer, request, 0, responsePayload);
  } catch (std::exception &e) {
    std::cout << "Error getting notifications: " << e.what() << std::endl;
    std::string responseString{"Failed to get notifications due to : " +
                           std::string(e.what())};
    responsePayload.AddMember("message", responseString, responsePayload.GetAllocator());
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::addFoodItemAttribute(
    std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
    rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  rapidjson::Document responsePayload;
  if (!responsePayload.IsObject()) {
        responsePayload.SetObject();
    }
  try {
    std::pair<uint64_t, uint64_t> data;
    data.deserialize(payload);
    uint64_t foodItemId = data.first;
    uint64_t attributeId = data.second;
    foodItemService->addAttributeToFoodItem(foodItemId, attributeId);
    std::vector<unsigned char> responsePayload;
    writeResponse(responseBuffer, request, 0, responsePayload);
  } catch (std::exception &e) {
    std::cout << "Error adding attribute: " << e.what() << std::endl;
    std::string responseString{"Failed to add attribute due to : " +
                           std::string(e.what())};
    std::vector<unsigned char> responsePayload = responseString.serialize();
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::getAllAttributes(std::shared_ptr<TcpSocket> socket,
                                       rapidjson::Document &request,
                                       rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  try {
    std::vector<std::pair<uint64_t, std::string>> attributes =
        foodItemService->getAllAttributes();
    Array<Pair<uint64_t, std::string>> attributesArray;
    for (auto &attribute : attributes) {
      attributesArray.push_back(
          Pair<uint64_t, std::string>{attribute.first, attribute.second});
    }
    auto payload = attributesArray.serialize();
    writeResponse(responseBuffer, request, 0, payload);
  } catch (std::exception &e) {
    std::cout << "Error getting attributes: " << e.what() << std::endl;
    std::string responseString{"Failed to get attributes due to : " +
                           std::string(e.what())};
    auto payload = responseString.serialize();
    writeResponse(responseBuffer, request, 400, payload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::viewFoodItemAttributes(
    std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
    rapidjson::Document &payload) {
  std::cout << "running view FoodItem Attributes\n";
  std::vector<unsigned char> responseBuffer;
  try {
    uint64_t foodItemId;
    foodItemId.deserialize(payload);
    std::vector<std::pair<uint64_t, std::string>> attributes =
        foodItemService->getFoodItemAttributes(foodItemId);

    Array<Pair<uint64_t, std::string>> attributesArray;
    for (auto &attribute : attributes) {
      attributesArray.push_back(
          Pair<uint64_t, std::string>{attribute.first, attribute.second});
    }
    std::vector<unsigned char> payload = attributesArray.serialize();
    writeResponse(responseBuffer, request, 0, payload);
  } catch (std::exception &e) {
    std::cout << "Error getting food item attributes: " << e.what()
              << std::endl;
    std::string responseString{"Failed to get food item attributes due to : " +
                           std::string(e.what())};
    std::vector<unsigned char> payload = responseString.serialize();
    writeResponse(responseBuffer, request, 400, payload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::removeAttribute(std::shared_ptr<TcpSocket> socket,
                                      rapidjson::Document &request,
                                      rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  try {
    Pair<uint64_t, uint64_t> data;
    data.deserialize(payload);
    uint64_t foodItemId = data.first;
    uint64_t attributeId = data.second;
    foodItemService->removeAttributeFromFoodItem(foodItemId, attributeId);
    std::vector<unsigned char> responsePayload;
    writeResponse(responseBuffer, request, 0, responsePayload);
  } catch (std::exception &e) {
    std::cout << "Error removing attribute: " << e.what() << std::endl;
    std::string responseString{"Failed to remove attribute due to : " +
                           std::string(e.what())};
    std::vector<unsigned char> responsePayload = responseString.serialize();
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool AdminController::addAttribute(std::shared_ptr<TcpSocket> socket,
                                   rapidjson::Document &request,
                                   rapidjson::Document &payload) {
  std::vector<unsigned char> responseBuffer;
  try {
    std::string attribute;
    attribute.deserialize(payload);
    if (foodItemService->addAttribute(attribute)) {
      std::vector<unsigned char> responsePayload;
      writeResponse(responseBuffer, request, 0, responsePayload);
    } else {
      std::string responseString{"Failed to add attribute"};
      std::vector<unsigned char> responsePayload = responseString.serialize();
      writeResponse(responseBuffer, request, 400, responsePayload);
    }
  } catch (std::exception &e) {
    std::cout << "Error adding attribute: " << e.what() << std::endl;
    std::string responseString{"Failed to add attribute due to : " +
                           std::string(e.what())};
    std::vector<unsigned char> responsePayload = responseString.serialize();
    writeResponse(responseBuffer, request, 400, responsePayload);
  }
  try {
    socket->sendData(responseBuffer);
  } catch (std::exception &e) {
    std::cout << "Error sending response: " << e.what() << std::endl;
    return false;
  }
  return true;
}