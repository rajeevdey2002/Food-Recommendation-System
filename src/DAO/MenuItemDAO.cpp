#include "MenuItemDAO.h"
#include <algorithm>
#include <stdexcept>

namespace DAO {

std::vector<DTO::MenuItem> MenuItemDAO::menuItems;

// Function to load menu items from database
std::vector<DTO::MenuItem> MenuItemDAO::loadFromDatabase() {
    // Replace with actual database loading logic
    return menuItems;
}

// Function to save menu items to database
void MenuItemDAO::saveToDatabase(const std::vector<DTO::MenuItem>& menuItems) {
    // Replace with actual database saving logic
    MenuItemDAO::menuItems = menuItems;
}

bool MenuItemDAO::addMenuItem(const DTO::MenuItem& menuItem) {
    auto menuItems = loadFromDatabase();
    menuItems.push_back(menuItem);
    saveToDatabase(menuItems);
    return true;
}

bool MenuItemDAO::deleteMenuItem(uint64_t menuItemId) {
    auto menuItems = loadFromDatabase();
    auto it = std::remove_if(menuItems.begin(), menuItems.end(),
                             [menuItemId](const DTO::MenuItem& item) {
                                 return item.menuItemId == menuItemId;
                             });
    if (it != menuItems.end()) {
        menuItems.erase(it, menuItems.end());
        saveToDatabase(menuItems);
        return true;
    }
    return false;
}

bool MenuItemDAO::updateMenuItem(const DTO::MenuItem& menuItem) {
    auto menuItems = loadFromDatabase();
    auto it = std::find_if(menuItems.begin(), menuItems.end(),
                           [&menuItem](const DTO::MenuItem& m) {
                               return m.menuItemId == menuItem.menuItemId;
                           });
    if (it != menuItems.end()) {
        *it = menuItem;
        saveToDatabase(menuItems);
        return true;
    }
    return false;
}

} // namespace DAO
