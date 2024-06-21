#pragma once

#include <vector>
#include "Menu.h"

namespace DAO {

class MenuDAO {
public:
    static std::vector<DTO::Menu> loadFromDatabase();
    static void saveToDatabase(const std::vector<DTO::Menu>& menus);
    static bool addMenu(const DTO::Menu& menu);
    static bool deleteMenu(uint64_t menuId);
    static bool updateMenu(const DTO::Menu& menu);

private:
    static std::vector<DTO::Menu> menus;
};

} // namespace DAO
