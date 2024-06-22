#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct MenuItem {
    uint64_t menuItemId;
    uint64_t menuId;
    uint64_t foodItemId;

    MenuItem(uint64_t id, uint64_t menuId, uint64_t foodItemId)
        : menuItemId(id), menuId(menuId), foodItemId(foodItemId) {}

    MenuItem(const rapidjson::Value& json) {
        menuItemId = json["menuItemId"].GetUint64();
        menuId = json["menuId"].GetUint64();
        foodItemId = json["foodItemId"].GetUint64();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("menuItemId", menuItemId, allocator);
        json.AddMember("menuId", menuId, allocator);
        json.AddMember("foodItemId", foodItemId, allocator);
    }
};

};
