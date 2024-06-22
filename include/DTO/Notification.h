#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct Notification {
    uint64_t notificationId;
    uint64_t userId;
    std::string message;
    bool isRead;
    std::string createdAt;

    Notification(uint64_t id, uint64_t userId, const std::string& message, bool isRead, const std::string& createdAt)
        : notificationId(id), userId(userId), message(message), isRead(isRead), createdAt(createdAt) {}

    Notification(const rapidjson::Value& json) {
        notificationId = json["notificationId"].GetUint64();
        userId = json["userId"].GetUint64();
        message = json["message"].GetString();
        isRead = json["isRead"].GetBool();
        createdAt = json["createdAt"].GetString();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("notificationId", notificationId, allocator);
        json.AddMember("userId", userId, allocator);
        json.AddMember("message", rapidjson::Value(message.c_str(), allocator), allocator);
        json.AddMember("isRead", isRead, allocator);
        json.AddMember("createdAt", rapidjson::Value(createdAt.c_str(), allocator), allocator);
    }
};

};
