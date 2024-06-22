#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct Role {
    uint64_t roleId;
    std::string roleName;

    Role(uint64_t id, const std::string& roleName)
        : roleId(id), roleName(roleName) {}

    Role(const rapidjson::Value& json) {
        roleId = json["roleId"].GetUint64();
        roleName = json["roleName"].GetString();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("roleId", roleId, allocator);
        json.AddMember("roleName", rapidjson::Value(roleName.c_str(), allocator), allocator);
    }
};

};
