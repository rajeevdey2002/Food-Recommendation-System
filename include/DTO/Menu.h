#pragma once

#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct Menu {
  uint64_t menuId;
  std::string menuName;
  uint64_t categoryId;
  bool isSurvey;
  std::string date;

  Menu() = default;
  Menu(uint64_t menuId, std::string menuName, uint64_t categoryId, bool isSurvey, std::string date)
      : menuId(menuId), menuName(menuName), categoryId(categoryId), isSurvey(isSurvey), date(date) {}

  std::string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("menuId", menuId.getValue(), allocator);
    doc.AddMember("menuName", rapidjson::Value(menuName.c_str(), allocator).Move(), allocator);
    doc.AddMember("categoryId", categoryId.getValue(), allocator);
    doc.AddMember("isSurvey", isSurvey, allocator);
    doc.AddMember("date", rapidjson::Value(date.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
  }

  static Menu fromJson(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    uint64_t menuId(doc["menuId"].GetUint64());
    std::string menuName(doc["menuName"].GetString());
    uint64_t categoryId(doc["categoryId"].GetUint64());
    bool isSurvey = doc["isSurvey"].GetBool();
    std::string date(doc["date"].GetString());

    return Menu(menuId, menuName, categoryId, isSurvey, date);
  }
};

}; // namespace DTO
