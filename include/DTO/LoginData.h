#pragma once

#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

struct LoginData {
  uint64_t userId;
  uint64_t roleId;
  std::string password;

  LoginData() : userId(0), roleId(0), password("") {}

  LoginData(uint64_t userId, uint64_t roleId, std::string password)
      : userId(userId), roleId(roleId), password(password) {}

  std::string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("userId", userId.getValue(), allocator);
    doc.AddMember("roleId", roleId.getValue(), allocator);
    doc.AddMember("password", rapidjson::Value(password.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
  }

  static LoginData fromJson(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    uint64_t userId(doc["userId"].GetUint64());
    uint64_t roleId(doc["roleId"].GetUint64());
    std::string password(doc["password"].GetString());

    return LoginData(userId, roleId, password);
  }
};
