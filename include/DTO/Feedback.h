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
  uint64_t menuId;
  uint64_t foodItemId;
  uint32_t rating;
  std::string comment;
  std::string date;

  Feedback(uint64_t feedbackId, uint64_t userId, uint64_t menuId,
           uint64_t foodItemId, uint32_t rating, std::string comment,
           std::string date)
      : feedbackId(feedbackId), userId(userId), menuId(menuId),
        foodItemId(foodItemId), rating(rating), comment(comment), date(date) {}

  std::string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("feedbackId", feedbackId, allocator);
    doc.AddMember("userId", userId, allocator);
    doc.AddMember("menuId", menuId, allocator);
    doc.AddMember("foodItemId", foodItemId, allocator);
    doc.AddMember("rating", rating, allocator);
    doc.AddMember("comment", rapidjson::Value(comment.c_str(), allocator).Move(), allocator);
    doc.AddMember("date", rapidjson::Value(date.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
  }

  static Feedback fromJson(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    uint64_t feedbackId = doc["feedbackId"].GetUint64();
    uint64_t userId = doc["userId"].GetUint64();
    uint64_t menuId = doc["menuId"].GetUint64();
    uint64_t foodItemId = doc["foodItemId"].GetUint64();
    uint32_t rating = doc["rating"].GetUint();
    std::string comment = doc["comment"].GetString();
    std::string date = doc["date"].GetString();

    return Feedback(feedbackId, userId, menuId, foodItemId, rating, comment, date);
  }
};

}
