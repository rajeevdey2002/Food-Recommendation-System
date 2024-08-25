#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace DTO {

struct Attribute {
  uint64_t attributeId;
  std::string attributeName;

  Attribute() = default;
  Attribute(uint64_t attributeId, std::string attributeName)
      : attributeId(attributeId), attributeName(attributeName) {}
};

}; // namespace DTO