#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct Preference {
    uint64_t preferenceId;
    uint64_t userId;
    std::string preferenceKey;
    std::string preferenceValue;

    Preference(uint64_t id, uint64_t userId, const std::string& preferenceKey, const std::string& preferenceValue)
        : preferenceId(id), userId(userId), preferenceKey(preferenceKey), preferenceValue(preferenceValue) {}

    Preference(const rapidjson::Value& json) {
        preferenceId = json["id"].GetUint64();
        userId = json["userId"].GetUint64();
        preferenceKey = json["preferenceKey"].GetString();
        preferenceValue = json["preferenceValue"].GetString();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("preferenceId", preferenceId, allocator);
        json.AddMember("userId", userId, allocator);
        json.AddMember("preferenceKey", rapidjson::Value(preferenceKey.c_str(), allocator), allocator);
        json.AddMember("preferenceValue", rapidjson::Value(preferenceValue.c_str(), allocator), allocator);
    }
};

};
