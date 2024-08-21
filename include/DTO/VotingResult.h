#pragma once

#include <cstdint>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DTO {

struct VotingResult {
  uint64_t foodItemId;
  uint64_t numberOfVotes;
  uint64_t numberOfPositiveVotes;
  uint64_t numberOfNegativeVotes;
  std::string foodItemName;

  VotingResult() = default;
  VotingResult(uint64_t foodItemId, uint64_t numberOfVotes, uint64_t numberOfPositiveVotes,
               uint64_t numberOfNegativeVotes, std::string foodItemName)
      : foodItemId(foodItemId), numberOfVotes(numberOfVotes),
        numberOfPositiveVotes(numberOfPositiveVotes),
        numberOfNegativeVotes(numberOfNegativeVotes),
        foodItemName(foodItemName) {}

  std::string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("foodItemId", foodItemId.getValue(), allocator);
    doc.AddMember("numberOfVotes", numberOfVotes.getValue(), allocator);
    doc.AddMember("numberOfPositiveVotes", numberOfPositiveVotes.getValue(), allocator);
    doc.AddMember("numberOfNegativeVotes", numberOfNegativeVotes.getValue(), allocator);
    doc.AddMember("foodItemName", rapidjson::Value(foodItemName.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
  }

  static VotingResult fromJson(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    uint64_t foodItemId(doc["foodItemId"].GetUint64());
    uint64_t numberOfVotes(doc["numberOfVotes"].GetUint64());
    uint64_t numberOfPositiveVotes(doc["numberOfPositiveVotes"].GetUint64());
    uint64_t numberOfNegativeVotes(doc["numberOfNegativeVotes"].GetUint64());
    std::string foodItemName(doc["foodItemName"].GetString());

    return VotingResult(foodItemId, numberOfVotes, numberOfPositiveVotes, numberOfNegativeVotes, foodItemName);
  }
};

} // namespace DTO
