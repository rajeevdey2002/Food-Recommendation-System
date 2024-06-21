#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct MenuType {
    uint64_t menuTypeId;
    std::string typeName;

    MenuType(uint64_t id, const std::string& typeName)
        : menuTypeId(id), typeName(typeName) {}

    MenuType(const rapidjson::Value& json) {
        menuTypeId = json["menuTypeId"].GetUint64();
        typeName = json["typeName"].GetString();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("menuTypeId", menuTypeId, allocator);
        json.AddMember("typeName", rapidjson::Value(typeName.c_str(), allocator), allocator);
    }
};

}; // namespace DTO
