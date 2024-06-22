#pragma once

#include <vector>
#include "FoodItemTypes.h"

namespace DAO {

class FoodItemTypesDAO {
public:
    static std::vector<DTO::FoodItemTypes> loadFromDatabase();
    static void saveToDatabase(const std::vector<DTO::FoodItemTypes>& foodItemTypes);
    static bool addFoodItemType(const DTO::FoodItemTypes& foodItemType);
    static bool deleteFoodItemType(uint64_t foodItemTypeId);
    static bool updateFoodItemType(const DTO::FoodItemTypes& foodItemType);

private:
    static std::vector<DTO::FoodItemTypes> foodItemTypes;
};

}
