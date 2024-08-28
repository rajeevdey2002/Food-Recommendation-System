#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {
struct DiscardFeedbackAnswer {
  uint64_t answerId;
  uint64_t questionId;
  uint64_t userId;
  std::string answer;

  DiscardFeedbackAnswer() : answerId(0), questionId(0), userId(0), answer("") {}

  DiscardFeedbackAnswer(uint64_t answerId, uint64_t questionId, uint64_t userId, std::string answer)
      : answerId(answerId), questionId(questionId), userId(userId), answer(answer) {}

  void toJson(rapidjson::Document &doc) const {
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("answerId", answerId, allocator);
    doc.AddMember("questionId", questionId, allocator);
    doc.AddMember("userId", userId, allocator);
    doc.AddMember("answer", rapidjson::Value(answer.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
  }

  static DiscardFeedbackAnswer fromJson(rapidjson::Document &doc) {
    uint64_t answerId(doc["answerId"].GetUint64());
    uint64_t questionId(doc["questionId"].GetUint64());
    uint64_t userId(doc["userId"].GetUint64());
    std::string answer(doc["answer"].GetString());

    return DiscardFeedbackAnswer(answerId, questionId, userId, answer);
  }
};
} // namespace DTO
