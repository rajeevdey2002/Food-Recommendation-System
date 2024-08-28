#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {
struct DiscardFeedbackQuestion {
  uint64_t questionId;
  uint64_t foodItemId;
  std::string question;

  DiscardFeedbackQuestion() : questionId(0), foodItemId(0), question("") {}

  DiscardFeedbackQuestion(uint64_t questionId, uint64_t foodItemId, std::string question)
      : questionId(questionId), foodItemId(foodItemId), question(question) {}

  void toJson(rapidjson::Document &doc) const {
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("questionId", questionId, allocator);
    doc.AddMember("foodItemId", foodItemId, allocator);
    doc.AddMember("question", rapidjson::Value(question.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
  }

  static DiscardFeedbackQuestion fromJson(rapidjson::Document &doc) {

    uint64_t questionId(doc["questionId"].GetUint64());
    uint64_t foodItemId(doc["foodItemId"].GetUint64());
    std::string question(doc["question"].GetString());

    return DiscardFeedbackQuestion(questionId, foodItemId, question);
  }
};
} // namespace DTO
