#pragma once

#include "Attribute.h"
#include "IAttributeDAO.h"
#include "server/DbConnection.h"
#include <memory>

namespace DAO {

class AttributeDAO : public IAttributeDAO {
  std::shared_ptr<DbConnection> dbConnection;

public:
  AttributeDAO();
  uint64_t addAttribute(std::string attributeName) override;
  bool removeAttribute(uint64_t attributeId) override;
  std::vector<DTO::Attribute> getAllAttributes() override;
  ~AttributeDAO() = default;
};

}; // namespace DAO