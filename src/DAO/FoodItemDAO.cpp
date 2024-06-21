#include "FoodItemDAO.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace DAO {

std::string FoodItemDAO::databaseFile = "foodItems.json";

bool FoodItemDAO::addFoodItem(const DTO::FoodItem& foodItem) {
    std::vector<DTO::FoodItem> foodItems = loadFromDatabase();
    foodItems.push_back(foodItem);
    saveToDatabase(foodItems);
    return true;
}

std::vector<DTO::FoodItem> FoodItemDAO::getAllFoodItems() {
    return loadFromDatabase();
}

DTO::FoodItem FoodItemDAO::getFoodItemById(uint64_t foodItemId) {
    std::vector<DTO::FoodItem> foodItems = loadFromDatabase();
    for (const auto& item : foodItems) {
        if (item.foodItemId == foodItemId) {
            return item;
        }
    }
    throw std::runtime_error("FoodItem not found");
}

bool FoodItemDAO::updateFoodItem(const DTO::FoodItem& foodItem) {
    std::vector<DTO::FoodItem> foodItems = loadFromDatabase();
    for (auto& item : foodItems) {
        if (item.foodItemId == foodItem.foodItemId) {
            item = foodItem;
            saveToDatabase(foodItems);
            return true;
        }
    }
    return false;
}

bool FoodItemDAO::deleteFoodItem(uint64_t foodItemId) {
    std::vector<DTO::FoodItem> foodItems = loadFromDatabase();
    
    // Loop through the vector and find the food item with the given id
    auto it = foodItems.begin();
    while (it != foodItems.end()) {
        if (it->foodItemId == foodItemId) {
            it = foodItems.erase(it);  // Erase the element and get the next iterator
        } else {
            ++it;  // Move to the next element
        }
    }

    // Save the modified vector back to the database
    saveToDatabase(foodItems);
    return true;
}

void FoodItemDAO::saveToDatabase(const std::vector<DTO::FoodItem>& foodItems) {
    std::ofstream file(databaseFile);
    rapidjson::Document doc;
    doc.SetArray();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    for (const auto& item : foodItems) {
        rapidjson::Value foodItemObj(rapidjson::kObjectType);
        foodItemObj.AddMember("foodItemId", item.foodItemId, allocator);
        foodItemObj.AddMember("name", rapidjson::Value(item.name.c_str(), allocator).Move(), allocator);
        foodItemObj.AddMember("description", rapidjson::Value(item.description.c_str(), allocator).Move(), allocator);
        foodItemObj.AddMember("price", item.price, allocator);
        doc.PushBack(foodItemObj, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    file << buffer.GetString();
}

std::vector<DTO::FoodItem> FoodItemDAO::loadFromDatabase() {
    std::ifstream file(databaseFile);
    if (!file.is_open()) {
        return {};
    }

    rapidjson::IStreamWrapper isw(file);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    std::vector<DTO::FoodItem> foodItems;
    for (const auto& item : doc.GetArray()) {
        uint64_t foodItemId = item["foodItemId"].GetUint64();
        std::string name = item["name"].GetString();
        std::string description = item["description"].GetString();
        double price = item["price"].GetDouble();
        foodItems.emplace_back(foodItemId, name, description, price);
    }

    return foodItems;
}

} // namespace DAO
