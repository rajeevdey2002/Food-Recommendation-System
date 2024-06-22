#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct Menu {
    uint64_t menuId;
    std::string name;
    std::string description;

    Menu(uint64_t id, const std::string& name, const std::string& description)
        : menuId(id), name(name), description(description) {}

    Menu(const rapidjson::Value& json) {
        menuId = json["menuId"].GetUint64();
        name = json["name"].GetString();
        description = json["description"].GetString();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("menuId", menuId, allocator);
        json.AddMember("name", rapidjson::Value(name.c_str(), allocator), allocator);
        json.AddMember("description", rapidjson::Value(description.c_str(), allocator), allocator);
    }
};

};
