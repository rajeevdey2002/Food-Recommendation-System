#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct FoodItem {
  uint64_t foodItemId;
  double price;
  bool availabilityStatus;
  bool isDiscarded;
  uint64_t foodItemTypeId;
  std::string itemName;

  FoodItem()
      : foodItemId(0), price(0), availabilityStatus(false), isDiscarded(false),
        foodItemTypeId(0), itemName("") {}

  FoodItem(uint64_t foodItemId, double price, bool availabilityStatus,
           bool isDiscarded, uint64_t foodItemTypeId, std::string itemName)
      : foodItemId(foodItemId), price(price),
        availabilityStatus(availabilityStatus), isDiscarded(isDiscarded),
        foodItemTypeId(foodItemTypeId), itemName(itemName) {}

  void toJson(rapidjson::Document &doc) const {
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("foodItemId", foodItemId, allocator);
    doc.AddMember("price", price, allocator);
    doc.AddMember("availabilityStatus", availabilityStatus, allocator);
    doc.AddMember("isDiscarded", isDiscarded, allocator);
    doc.AddMember("foodItemTypeId", foodItemTypeId, allocator);
    doc.AddMember("itemName", rapidjson::Value(itemName.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
  }

  static FoodItem fromJson(rapidjson::Document &doc) {
    uint64_t foodItemId(doc["foodItemId"].GetUint64());
    double price(doc["price"].GetDouble());
    bool availabilityStatus = doc["availabilityStatus"].GetBool();
    bool isDiscarded = doc["isDiscarded"].GetBool();
    uint64_t foodItemTypeId(doc["foodItemTypeId"].GetUint64());
    std::string itemName(doc["itemName"].GetString());

    return FoodItem(foodItemId, price, availabilityStatus, isDiscarded, foodItemTypeId, itemName);
  }
};

} // namespace DTO
