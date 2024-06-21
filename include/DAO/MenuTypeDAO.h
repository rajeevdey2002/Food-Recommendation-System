#pragma once

#include <vector>
#include "MenuType.h"

namespace DAO {

class MenuTypeDAO {
public:
    static std::vector<DTO::MenuType> loadFromDatabase();
    static void saveToDatabase(const std::vector<DTO::MenuType>& menuTypes);
    static bool addMenuType(const DTO::MenuType& menuType);
    static bool deleteMenuType(uint64_t menuTypeId);
    static bool updateMenuType(const DTO::MenuType& menuType);

private:
    static std::vector<DTO::MenuType> menuTypes;
};

} // namespace DAO
