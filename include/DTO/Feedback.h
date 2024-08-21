#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct Feedback {
  uint64_t feedbackId;
  uint64_t userId;
  uint64_t foodItemId;
  bool preference;
  std::string date;

  Feedback()
      : preference{false}, date{""}, userId{0}, feedbackId{0}, foodItemId{0} {}

  Feedback(uint64_t feedbackId, uint64_t userId, uint64_t foodItemId, bool preference,
           std::string date)
      : feedbackId(feedbackId), userId(userId), foodItemId(foodItemId),
        preference(preference), date(date) {}

  std::string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("feedbackId", feedbackId.getValue(), allocator);
    doc.AddMember("userId", userId.getValue(), allocator);
    doc.AddMember("foodItemId", foodItemId.getValue(), allocator);
    doc.AddMember("preference", preference, allocator);
    doc.AddMember("date", rapidjson::Value(date.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
  }

  static Feedback fromJson(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    uint64_t feedbackId(doc["feedbackId"].GetUint64());
    uint64_t userId(doc["userId"].GetUint64());
    uint64_t foodItemId(doc["foodItemId"].GetUint64());
    bool preference = doc["preference"].GetBool();
    std::string date(doc["date"].GetString());

    return Feedback(feedbackId, userId, foodItemId, preference, date);
  }
};

} // namespace DTO
