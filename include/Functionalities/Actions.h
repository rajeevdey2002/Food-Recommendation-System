#pragma once

#include <rapidjson/document.h>
#include <vector>

namespace Controller {

enum class AdminActions {
  ADD_FOOD_ITEM,
  REMOVE_FOOD_ITEM,
  UPDATE_FOOD_ITEM,
  GET_FOOD_ITEMS,
  ADD_USER,
  VIEW_NOTIFICATIONS,
  ADD_FOOD_ITEM_ATTRIBUTE,
  GET_ALL_ATTRIBUTES,
  VIEW_FOOD_ITEM_ATTRIBUTES,
  REMOVE_ATTRIBUTE,
  ADD_ATTRIBUTE
};

enum class ChefActions {
  GET_RECOMMENDED_MENU,
  ROLLOUT_MENU,
  CREATE_MENU,
  VIEW_ROLLOUT_MENU,
  VIEW_MENU,
  UPDATE_MENU,
  VIEW_ROLLOUT_FEEDBACK,
  VIEW_NOTIFICATIONS,
  VIEW_FOOD_ITEMS,
  ADD_DISCARD_FEEDBACK_QUESTION,
  DISCARD_FOOD_ITEM,
  VIEW_DISCARD_FEEDBACK_ANSWER_SENTIMENTS,
  VIEW_DISCARD_FEEDBACK_QUESTIONS,
  GET_FOOD_ITEMS_BELOW_RATING,
  GET_DISCARDED_FOOD_ITEMS
};

enum class EmployeeActions {
  VIEW_MENU,
  VIEW_MENU_ROLLOUT,
  SEND_FEEDBACK,
  VIEW_NOTIFICATIONS,
  WRITE_REVIEW,
  GET_ATTRIBUTES,
  VIEW_FOOD_ITEM_ATTRIBUTES,
  ADD_FOOD_PREFERENCES,
  DELETE_FOOD_PREFERENCES,
  GET_FOOD_PREFERENCES,
  GET_DISCARDED_FOOD_ITEMS,
  GET_DISCARDED_FOOD_ITEM_QUESTIONS,
  ADD_DISCARDED_FOOD_ITEM_ANSWER
};

template <typename EnumType>
int enumToInt(EnumType action) {
    return static_cast<int>(action);
}

AdminActions intToAdminActions(int action);
ChefActions intToChefActions(int action);
EmployeeActions intToEmployeeActions(int action);

void writeResponse(std::vector<unsigned char> &buffer, 
                   rapidjson::Document &request, 
                   int statusCode, 
                   rapidjson::Document &payload);

} // namespace Controller