#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct User {
  uint64_t userId;
  std::string name;
  std::string password;
  uint64_t roleId;
  uint64_t lastNotificationId;

  User() = default;
  User(uint64_t userId, std::string name, std::string password, uint64_t roleId, uint64_t lastNotificationId)
      : userId(userId), name(name), password(password), roleId(roleId), lastNotificationId(lastNotificationId) {}

  void toJson(rapidjson::Document &doc) const {
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("userId", userId, allocator);
    doc.AddMember("name", rapidjson::Value(name.c_str(), allocator).Move(), allocator);
    doc.AddMember("password", rapidjson::Value(password.c_str(), allocator).Move(), allocator);
    doc.AddMember("roleId", roleId, allocator);
    doc.AddMember("lastNotificationId", lastNotificationId, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
  }

  static User fromJson(rapidjson::Document &doc) {
    uint64_t userId = doc["userId"].GetUint64();
    std::string name = doc["name"].GetString();
    std::string password = doc["password"].GetString();
    uint64_t roleId = doc["roleId"].GetUint64();
    uint64_t lastNotificationId = doc["lastNotificationId"].GetUint64();

    return User(userId, name, password, roleId, lastNotificationId);
  }
};

}
