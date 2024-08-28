#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct UserActivity {
  uint64_t activityId;
  uint64_t userId;
  uint64_t activityTypeId;
  uint64_t activityTime;

  UserActivity() = default;
  UserActivity(uint64_t activityId, uint64_t userId, uint64_t activityTypeId, uint64_t activityTime)
      : activityId(activityId), userId(userId), activityTypeId(activityTypeId), activityTime(activityTime) {}

  void toJson(rapidjson::Document &doc) const {
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("activityId", activityId, allocator);
    doc.AddMember("userId", userId, allocator);
    doc.AddMember("activityTypeId", activityTypeId, allocator);
    doc.AddMember("activityTime", activityTime, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
  }

  static UserActivity fromJson(rapidjson::Document &doc) {
    uint64_t activityId(doc["activityId"].GetUint64());
    uint64_t userId(doc["userId"].GetUint64());
    uint64_t activityTypeId(doc["activityTypeId"].GetUint64());
    uint64_t activityTime(doc["activityTime"].GetUint64());

    return UserActivity(activityId, userId, activityTypeId, activityTime);
  }
};

} // namespace DTO
