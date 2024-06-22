#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct FoodItemTypes {
    uint64_t foodItemTypeId;
    std::string typeName;

    FoodItemTypes(uint64_t id, const std::string& name)
        : foodItemTypeId(id), typeName(name) {}

    FoodItemTypes(const rapidjson::Value& json) {
        foodItemTypeId = json["foodItemTypeId"].GetUint64();
        typeName = json["typeName"].GetString();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("id", foodItemTypeId, allocator);
        json.AddMember("typeName", rapidjson::Value(typeName.c_str(), allocator), allocator);
    }
};

};