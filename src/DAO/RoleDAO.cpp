#include "RoleDAO.h"
#include <algorithm>
#include <stdexcept>

namespace DAO {

std::vector<DTO::Role> RoleDAO::roles;

std::vector<DTO::Role> RoleDAO::loadFromDatabase() {
    return roles;
}

void RoleDAO::saveToDatabase(const std::vector<DTO::Role>& roles) {
    RoleDAO::roles = roles;
}

bool RoleDAO::addRole(const DTO::Role& role) {
    auto roles = loadFromDatabase();
    roles.push_back(role);
    saveToDatabase(roles);
    return true;
}

bool RoleDAO::deleteRole(uint64_t roleId) {
    auto roles = loadFromDatabase();
    auto it = std::remove_if(roles.begin(), roles.end(),
                             [roleId](const DTO::Role& item) {
                                 return item.roleId == roleId;
                             });
    if (it != roles.end()) {
        roles.erase(it, roles.end());
        saveToDatabase(roles);
        return true;
    }
    return false;
}

bool RoleDAO::updateRole(const DTO::Role& role) {
    auto roles = loadFromDatabase();
    auto it = std::find_if(roles.begin(), roles.end(),
                           [&role](const DTO::Role& r) {
                               return r.roleId == role.roleId;
                           });
    if (it != roles.end()) {
        *it = role;
        saveToDatabase(roles);
        return true;
    }
    return false;
}

}
