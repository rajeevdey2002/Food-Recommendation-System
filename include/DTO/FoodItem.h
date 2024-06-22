#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct FoodItem {
  uint64_t foodItemId;
  std::string name;
  std::string description;
  double price;

  FoodItem(uint64_t foodItemId, std::string name, std::string description, double price)
      : foodItemId(foodItemId), name(name), description(description), price(price) {}

  std::string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("foodItemId", foodItemId, allocator);
    doc.AddMember("name", rapidjson::Value(name.c_str(), allocator).Move(), allocator);
    doc.AddMember("description", rapidjson::Value(description.c_str(), allocator).Move(), allocator);
    doc.AddMember("price", price, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
  }

  static FoodItem fromJson(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    uint64_t foodItemId = doc["foodItemId"].GetUint64();
    std::string name = doc["name"].GetString();
    std::string description = doc["description"].GetString();
    double price = doc["price"].GetDouble();

    return FoodItem(foodItemId, name, description, price);
  }
};

}
