#include "server/controller/ChefController.h"
#include "Category.h"
#include "DTO/VotingResult.h"
#include "DiscardFeedbackAnswer.h"
#include "DiscardFeedbackQuestion.h"
#include "Feedback.h"
#include "FoodItem.h"
#include "Functionalities/Actions.h"
#include "MenuItem.h"
#include <regex>
#include <unordered_map>

using Controller::ChefController;

ChefController::ChefController(
    std::shared_ptr<Service::UserService> userService,
    std::shared_ptr<Service::FoodItemService> foodItemService,
    std::shared_ptr<Service::MenuService> menuService,
    std::shared_ptr<Service::RecommendationService> recommendationService)
    : userService(userService), foodItemService(foodItemService),
      menuService(menuService), recommendationService(recommendationService) {
  registerActions();
}

void ChefController::registerActions() {
  actions.insert(
      {ChefActions::VIEW_FOOD_ITEMS,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewFoodItems(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::GET_RECOMMENDED_MENU,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->getRecommendedMenu(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::CREATE_MENU,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->createMenu(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::VIEW_MENU,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewMenu(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::VIEW_ROLLOUT_MENU,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewRolloutMenu(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::UPDATE_MENU,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->updateMenu(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::VIEW_ROLLOUT_FEEDBACK,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewRolloutFeedback(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::VIEW_NOTIFICATIONS,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewNotifications(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::ADD_DISCARD_FEEDBACK_QUESTION,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->addDiscardFeedbackQuestion(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::DISCARD_FOOD_ITEM,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->discardFoodItem(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::VIEW_DISCARD_FEEDBACK_ANSWER_SENTIMENTS,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewDiscardFeedbackAnswerSentiments(socket, request,
                                                          payload);
       }});
  actions.insert(
      {ChefActions::VIEW_DISCARD_FEEDBACK_QUESTIONS,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->viewDiscardFeedbackQuestions(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::GET_FOOD_ITEMS_BELOW_RATING,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->getFoodItemsBelowRating(socket, request, payload);
       }});
  actions.insert(
      {ChefActions::GET_DISCARDED_FOOD_ITEMS,
       [this](std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
              rapidjson::Document &payload) -> bool {
         return this->getDiscardedFoodItems(socket, request, payload);
       }});
}

bool ChefController::handleRequest(TcpSocket socket, rapidjson::Document &request,
                                   rapidjson::Document &payload) {
  if (request.HasMember("action") && request["action"].IsInt()) {
    int action = request["action"].GetInt();
    if (actions.count((ChefActions)action) > 0)
    {
      std::shared_ptr<TcpSocket> socketPtr =
      std::make_shared<TcpSocket>(std::move(socket));
      return actions[(ChefActions)action](socketPtr, request, payload);
    }
  }
  return false;
}

bool ChefController::viewFoodItems(std::shared_ptr<TcpSocket> socket,
                                   rapidjson::Document &request,
                                   rapidjson::Document &payload) {
  U64 categoryId;
  try {
    categoryId.deserialize(payload);
    std::vector<DTO::FoodItem> foodItems =
        foodItemService->getFoodItemsByCategory(
            (DTO::Category)(uint64_t)categoryId);
    Array<DTO::FoodItem> foodItemsArray(foodItems);
    std::vector<unsigned char> response;
    auto serialized = foodItemsArray.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
    return true;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
}

bool ChefController::getRecommendedMenu(std::shared_ptr<TcpSocket> socket,
                                        rapidjson::Document &request,
                                        rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  Pair<U64, U32> data;
  try {
    data.deserialize(payload);
    uint64_t categoryId = data.first;
    uint32_t count = data.second;
    std::vector<DTO::FoodItem> recommendedMenu =
        recommendationService->getRecommendedFoodItems(
            (DTO::Category)categoryId, count);
    Array<DTO::FoodItem> recommendedMenuArray(recommendedMenu);
    auto menuSerialized = recommendedMenuArray.serialize();
    writeResponse(response, request, 0, menuSerialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::createMenu(std::shared_ptr<TcpSocket> socket,
                                rapidjson::Document &request,
                                rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  Pair<DTO::Menu, Array<DTO::MenuItem>> requestData;
  try {
    requestData.deserialize(payload);
    DTO::Menu menu = requestData.first;
    std::vector<DTO::MenuItem> menuItems = requestData.second;
    menuService->addMenu(menu, menuItems);
    auto serialized = std::vector<unsigned char>();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::viewMenu(std::shared_ptr<TcpSocket> socket,
                              rapidjson::Document &request,
                              rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  SString date;
  try {
    date.deserialize(payload);
    std::vector<std::pair<DTO::Menu, std::vector<DTO::MenuItem>>> menus =
        menuService->getMenuByDate(date);
    std::cout << "Input date : " << (std::string)date << std::endl;
    std::cout << "menu size : " << menus.size() << std::endl;
    Array<Pair<DTO::Menu, Array<DTO::MenuItem>>> menuArray;
    for (auto &menu : menus) {
      Array<DTO::MenuItem> menuItems(menu.second);
      menuArray.push_back(
          Pair<DTO::Menu, Array<DTO::MenuItem>>{menu.first, menuItems});
    }
    auto serialized = menuArray.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::viewRolloutMenu(std::shared_ptr<TcpSocket> socket,
                                     rapidjson::Document &request,
                                     rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  SString date;
  try {
    date.deserialize(payload);
    auto menus = menuService->getServeyMenu(date);
    // get menu Items
    Array<Pair<DTO::Menu, Array<DTO::MenuItem>>> menuArray;
    for (auto &menu : menus) {
      auto menuItems = menuService->getMenuItems(menu.menuId);
      Array<DTO::MenuItem> menuItemsArray(menuItems);
      menuArray.push_back(
          Pair<DTO::Menu, Array<DTO::MenuItem>>{menu, menuItemsArray});
    }
    auto serialized = menuArray.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::updateMenu(std::shared_ptr<TcpSocket> socket,
                                rapidjson::Document &request,
                                rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  Pair<DTO::Menu, Array<DTO::MenuItem>> requestData;
  try {
    requestData.deserialize(payload);
    DTO::Menu menu = requestData.first;
    std::vector<DTO::MenuItem> menuItems = requestData.second;
    menuService->updateMenu(menu, menuItems);
    auto serialized = std::vector<unsigned char>();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::viewRolloutFeedback(std::shared_ptr<TcpSocket> socket,
                                         rapidjson::Document &request,
                                         rapidjson::Document &payload) {
  Pair<U64, SString> data;
  try {
    data.deserialize(payload);
    DTO::Category category = (DTO::Category)(uint64_t)data.first;
    SString date = data.second;
    std::cout << "input date " << (std::string)date << "\n";
    auto menus = menuService->getServeyMenu(date, category);
    std::cout << "menu size : " << menus.size() << std::endl;
    std::unordered_map<std::string, std::vector<DTO::Feedback>> feedbacks;
    int day = getDay(date);
    int month = getMonth(date);
    int year = getYear(date);
    std::string previousDate = getPreviousDate(day, month, year);
    for (auto &menu : menus) {
      auto menuItems = menuService->getMenuItems(menu.menuId);
      auto foodItems = menuService->getFoodItems(menuItems);
      for (auto &foodItem : foodItems) {
        if (feedbacks.find(foodItem.itemName) == feedbacks.end()) {
          feedbacks[foodItem.itemName] = foodItemService->getAllFeedback(
              foodItem.foodItemId, previousDate);
        } else {
          auto feedback = foodItemService->getAllFeedback(foodItem.foodItemId,
                                                          previousDate);
          feedbacks[foodItem.itemName].insert(
              feedbacks[foodItem.itemName].end(), feedback.begin(),
              feedback.end());
        }
      }
    }

    std::vector<DTO::VotingResult> votingResults;
    for (auto &feedback : feedbacks) {
      uint64_t positiveVotes = 0;
      uint64_t negativeVotes = 0;
      for (auto &f : feedback.second) {
        if (f.preference) {
          positiveVotes++;
        } else {
          negativeVotes++;
        }
      }
      if (feedback.second.size() > 0) {
        votingResults.emplace_back(DTO::VotingResult{
            feedback.second[0].foodItemId, feedback.second.size(),
            positiveVotes, negativeVotes, feedback.first});
      }
    }
    Array<DTO::VotingResult> votingResultsArray(votingResults);
    std::vector<unsigned char> response;
    auto serialized = votingResultsArray.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::viewNotifications(std::shared_ptr<TcpSocket> socket,
                                       rapidjson::Document &request,
                                       rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  U64 userId;
  try {
    userId.deserialize(payload);
    std::vector<DTO::Notification> notifications =
        userService->getUnreadNotifications(userId);
    Array<DTO::Notification> notificationsArray(notifications);
    auto serialized = notificationsArray.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::addDiscardFeedbackQuestion(
    std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
    rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  Pair<SString, U64> questionFoodItemPair;
  try {
    questionFoodItemPair.deserialize(payload);
    foodItemService->addDiscardFeedbackQuestion(questionFoodItemPair.first,
                                                questionFoodItemPair.second);
    auto serialized = std::vector<unsigned char>();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::discardFoodItem(std::shared_ptr<TcpSocket> socket,
                                     rapidjson::Document &request,
                                     rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  U64 foodItemId;
  try {
    foodItemId.deserialize(payload);
    DTO::FoodItem foodItem = foodItemService->getFoodItemById(foodItemId);
    foodItem.isDiscarded = true;
    foodItemService->updateFoodItem(foodItem);
    auto serialized = std::vector<unsigned char>();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::viewDiscardFeedbackAnswerSentiments(
    std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
    rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  U64 questionId;
  try {
    questionId.deserialize(payload);
    std::vector<DTO::DiscardFeedbackAnswer> answers =
        foodItemService->getAnswerByQuestionId(questionId);
    std::vector<std::string> answerStrings;
    for (auto &answer : answers) {
      answerStrings.push_back(answer.answer);
    }
    std::vector<std::pair<double, std::vector<std::string>>> result =
        recommendationService->getSentiment(answerStrings);
    Array<Pair<Double, Array<SString>>> sentimentResults;
    for (auto &pair : result) {
      Array<SString> words;
      for (auto &word : pair.second) {
        words.push_back(word);
      }
      Pair<Double, Array<SString>> scoreWordsPair{pair.first, words};
      sentimentResults.push_back(scoreWordsPair);
    }
    std::vector<unsigned char> serialized = sentimentResults.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::viewDiscardFeedbackQuestions(
    std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
    rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  U64 foodItemId;
  try {
    foodItemId.deserialize(payload);
    std::vector<DTO::DiscardFeedbackQuestion> questions =
        foodItemService->getQuestionByFoodItemId(foodItemId);
    Array<DTO::DiscardFeedbackQuestion> questionsArray;
    for (auto &question : questions) {
      questionsArray.push_back(question);
    }
    auto serialized = questionsArray.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::getFoodItemsBelowRating(
    std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
    rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  Double rating;
  try {
    rating.deserialize(payload);
    std::vector<DTO::FoodItem> foodItems =
        recommendationService->getFoodItemsBelowRating(rating);
    Array<DTO::FoodItem> foodItemsArray;
    for (auto &foodItem : foodItems) {
      foodItemsArray.push_back(foodItem);
    }
    auto serialized = foodItemsArray.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}

bool ChefController::getDiscardedFoodItems(
    std::shared_ptr<TcpSocket> socket, rapidjson::Document &request,
    rapidjson::Document &payload) {
  std::vector<unsigned char> response;
  try {
    std::vector<DTO::FoodItem> foodItems =
        foodItemService->getDiscardedFoodItems();
    Array<DTO::FoodItem> foodItemsArray;
    for (auto &foodItem : foodItems) {
      foodItemsArray.push_back(foodItem);
    }
    auto serialized = foodItemsArray.serialize();
    writeResponse(response, request, 0, serialized);
    socket->sendData(response);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    SString error("Error  : " + std::string(e.what()));
    std::vector<unsigned char> response;
    auto serialized = error.serialize();
    writeResponse(response, request, 400, serialized);
    socket->sendData(response);
    return false;
  }
  return true;
}