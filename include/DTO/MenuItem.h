#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct MenuItem {
  uint64_t menuItemId;
  uint64_t foodItemId;
  uint64_t menuId;
  uint32_t quantity;

  MenuItem() : menuItemId(0), foodItemId(0), menuId(0), quantity(0) {}
  MenuItem(uint64_t menuItemId, uint64_t foodItemId, uint64_t menuId, uint32_t quantity)
      : menuItemId(menuItemId), foodItemId(foodItemId), menuId(menuId), quantity(quantity) {}

  std::string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("menuItemId", menuItemId, allocator);
    doc.AddMember("foodItemId", foodItemId, allocator);
    doc.AddMember("menuId", menuId, allocator);
    doc.AddMember("quantity", quantity, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
  }

  static MenuItem fromJson(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    uint64_t menuItemId(doc["menuItemId"].GetUint64());
    uint64_t foodItemId(doc["foodItemId"].GetUint64());
    uint64_t menuId(doc["menuId"].GetUint64());
    uint32_t quantity(doc["quantity"].GetUint());

    return MenuItem(menuItemId, foodItemId, menuId, quantity);
  }
};

}; // namespace DTO
