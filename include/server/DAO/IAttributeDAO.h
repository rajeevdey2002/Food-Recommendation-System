#pragma once

#include "Attribute.h"

namespace DAO {

class IAttributeDAO {
public:
  virtual uint64_t addAttribute(std::string attributeName) = 0;
  virtual bool removeAttribute(uint64_t attributeId) = 0;
  virtual std::vector<DTO::Attribute> getAllAttributes() = 0;
  virtual ~IAttributeDAO() = default;
};

}; // namespace DAO