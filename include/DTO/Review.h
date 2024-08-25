#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>

namespace DTO {

struct Review {
  uint64_t ReviewId;
  uint64_t userId;
  uint64_t foodItemId;
  uint32_t rating;
  std::string comment;
  std::string date;

  Review()
      : ReviewId(0), userId(0), foodItemId(0), rating(0), comment(""),
        date("") {}
  Review(uint64_t ReviewId, uint64_t userId, uint64_t foodItemId, uint32_t rating,
         std::string comment, std::string date)
      : ReviewId(ReviewId), userId(userId), foodItemId(foodItemId),
        rating(rating), comment(comment), date(date) {}

  std::string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("ReviewId", ReviewId, allocator);
    doc.AddMember("userId", userId, allocator);
    doc.AddMember("foodItemId", foodItemId, allocator);
    doc.AddMember("rating", rating, allocator);
    doc.AddMember("comment", rapidjson::Value().SetString(comment.c_str(), allocator), allocator);
    doc.AddMember("date", rapidjson::Value().SetString(date.c_str(), allocator), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
  }

  static Review fromJson(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    uint64_t ReviewId(doc["ReviewId"].GetUint64());
    uint64_t userId(doc["userId"].GetUint64());
    uint64_t foodItemId(doc["foodItemId"].GetUint64());
    uint32_t rating(doc["rating"].GetUint());
    std::string comment(doc["comment"].GetString());
    std::string date(doc["date"].GetString());

    return Review(ReviewId, userId, foodItemId, rating, comment, date);
  }
};

}; // namespace DTO
