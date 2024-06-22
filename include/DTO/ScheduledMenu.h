#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct ScheduledMenu {
    uint64_t scheduledMenuId;
    uint64_t menuId;
    std::string scheduledDate;

    ScheduledMenu(uint64_t id, uint64_t menuId, const std::string& scheduledDate)
        : scheduledMenuId(id), menuId(menuId), scheduledDate(scheduledDate) {}

    ScheduledMenu(const rapidjson::Value& json) {
        scheduledMenuId = json["scheduledMenuId"].GetUint64();
        menuId = json["menuId"].GetUint64();
        scheduledDate = json["scheduledDate"].GetString();
    }

    void toJSON(rapidjson::Document& doc, rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const {
        json.SetObject();
        json.AddMember("id", scheduledMenuId, allocator);
        json.AddMember("menuId", menuId, allocator);
        json.AddMember("scheduledDate", rapidjson::Value(scheduledDate.c_str(), allocator), allocator);
    }
};

};
