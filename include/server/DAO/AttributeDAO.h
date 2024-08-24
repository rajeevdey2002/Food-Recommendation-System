#pragma once

#include "Attribute.h"
#include "IAttributeDAO.h"
#include "server/DatabaseConnection.h"
#include <memory>

namespace DAO {

class AttributeDAO : public IAttributeDAO {
  std::shared_ptr<DatabaseConnection> dbConnection;

public:
  AttributeDAO();
  uint64_t addAttribute(std::string attributeName) override;
  bool removeAttribute(uint64_t attributeId) override;
  std::vector<DTO::Attribute> getAllAttributes() override;
  ~AttributeDAO() = default;
};

}; // namespace DAO