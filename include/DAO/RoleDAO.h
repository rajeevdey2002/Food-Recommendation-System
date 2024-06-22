#pragma once

#include <vector>
#include "Role.h"

namespace DAO {

class RoleDAO {
public:
    static std::vector<DTO::Role> loadFromDatabase();
    static void saveToDatabase(const std::vector<DTO::Role>& roles);
    static bool addRole(const DTO::Role& role);
    static bool deleteRole(uint64_t roleId);
    static bool updateRole(const DTO::Role& role);

private:
    static std::vector<DTO::Role> roles;
};

}
