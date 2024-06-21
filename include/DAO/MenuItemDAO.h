#pragma once

#include <vector>
#include "MenuItem.h"

namespace DAO {

class MenuItemDAO {
public:
    static std::vector<DTO::MenuItem> loadFromDatabase();
    static void saveToDatabase(const std::vector<DTO::MenuItem>& menuItems);
    static bool addMenuItem(const DTO::MenuItem& menuItem);
    static bool deleteMenuItem(uint64_t menuItemId);
    static bool updateMenuItem(const DTO::MenuItem& menuItem);

private:
    static std::vector<DTO::MenuItem> menuItems;
};

} // namespace DAO
