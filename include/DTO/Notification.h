#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>

namespace DTO {

struct Notification {
  uint64_t notificationId;
  std::string message;
  std::string date;

  Notification() : notificationId(0), message(""), date("") {}
  Notification(uint64_t notificationId, std::string message, std::string date)
      : notificationId(notificationId), message(message), date(date) {}

  void toJson(rapidjson::Document &doc) const {
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("notificationId", notificationId, allocator);
    doc.AddMember("message", rapidjson::Value().SetString(message.c_str(), allocator), allocator);
    doc.AddMember("date", rapidjson::Value().SetString(date.c_str(), allocator), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
  }

  static Notification fromJson(rapidjson::Document &doc) {
    uint64_t notificationId(doc["notificationId"].GetUint64());
    std::string message(doc["message"].GetString());
    std::string date(doc["date"].GetString());

    return Notification(notificationId, message, date);
  }
};

}; // namespace DTO
