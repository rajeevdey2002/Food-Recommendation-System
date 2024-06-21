#include "FoodItemTypesDAO.h"
#include <algorithm>  // For std::find_if
#include <stdexcept>  // For std::runtime_error

namespace DAO {

std::vector<DTO::FoodItemTypes> FoodItemTypesDAO::foodItemTypes;

// Function to load food item types from database
std::vector<DTO::FoodItemTypes> FoodItemTypesDAO::loadFromDatabase() {
    // Replace with actual database loading logic
    return foodItemTypes;
}

// Function to save food item types to database
void FoodItemTypesDAO::saveToDatabase(const std::vector<DTO::FoodItemTypes>& foodItemTypes) {
    // Replace with actual database saving logic
    FoodItemTypesDAO::foodItemTypes = foodItemTypes;
}

bool FoodItemTypesDAO::addFoodItemType(const DTO::FoodItemTypes& foodItemType) {
    auto foodItemTypes = loadFromDatabase();
    foodItemTypes.push_back(foodItemType);
    saveToDatabase(foodItemTypes);
    return true;
}

bool FoodItemTypesDAO::deleteFoodItemType(uint64_t foodItemTypeId) {
    auto foodItemTypes = loadFromDatabase();
    auto it = std::remove_if(foodItemTypes.begin(), foodItemTypes.end(),
                             [foodItemTypeId](const DTO::FoodItemTypes& item) {
                                 return item.foodItemTypeId == foodItemTypeId;
                             });
    if (it != foodItemTypes.end()) {
        foodItemTypes.erase(it, foodItemTypes.end());
        saveToDatabase(foodItemTypes);
        return true;
    }
    return false;
}

bool FoodItemTypesDAO::updateFoodItemType(const DTO::FoodItemTypes& foodItemType) {
    auto foodItemTypes = loadFromDatabase();
    auto it = std::find_if(foodItemTypes.begin(), foodItemTypes.end(),
                           [&foodItemType](const DTO::FoodItemTypes& item) {
                               return item.foodItemTypeId == foodItemType.foodItemTypeId;
                           });
    if (it != foodItemTypes.end()) {
        *it = foodItemType;
        saveToDatabase(foodItemTypes);
        return true;
    }
    return false;
}

} // namespace DAO
