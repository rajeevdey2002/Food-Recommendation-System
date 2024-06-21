#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "FoodItem.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DAO {

class FoodItemDAO {
public:
    static bool addFoodItem(const DTO::FoodItem& foodItem);
    static std::vector<DTO::FoodItem> getAllFoodItems();
    static DTO::FoodItem getFoodItemById(uint64_t foodItemId);
    static bool updateFoodItem(const DTO::FoodItem& foodItem);
    static bool deleteFoodItem(uint64_t foodItemId);

private:
    static std::string databaseFile;
    static void saveToDatabase(const std::vector<DTO::FoodItem>& foodItems);
    static std::vector<DTO::FoodItem> loadFromDatabase();
};

} // namespace DAO
