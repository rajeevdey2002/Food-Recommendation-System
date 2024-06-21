#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct Login {
    uint64_t id;
    uint64_t userId;
    uint64_t roleId;
    std::string loginTime;
    std::string logoutTime;

    Login(uint64_t id, uint64_t userId, uint64_t roleId, const std::string& loginTime, const std::string& logoutTime)
        : id(id), userId(userId), roleId(roleId), loginTime(loginTime), logoutTime(logoutTime) {}

    Login(const rapidjson::Value& json) {
        id = json["id"].GetUint64();
        userId = json["userId"].GetUint64();
        roleId = json["roleId"].GetUint64();
        loginTime = json["loginTime"].GetString();
        logoutTime = json["logoutTime"].GetString();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("id", id, allocator);
        json.AddMember("userId", userId, allocator);
        json.AddMember("roleId", roleId, allocator);
        json.AddMember("loginTime", rapidjson::Value(loginTime.c_str(), allocator), allocator);
        json.AddMember("logoutTime", rapidjson::Value(logoutTime.c_str(), allocator), allocator);
    }
};

} // namespace DTO
