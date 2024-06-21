#include "MenuDAO.h"
#include <algorithm>
#include <stdexcept>

namespace DAO {

std::vector<DTO::Menu> MenuDAO::menus;

// Function to load menus from database
std::vector<DTO::Menu> MenuDAO::loadFromDatabase() {
    // Replace with actual database loading logic
    return menus;
}

// Function to save menus to database
void MenuDAO::saveToDatabase(const std::vector<DTO::Menu>& menus) {
    // Replace with actual database saving logic
    MenuDAO::menus = menus;
}

bool MenuDAO::addMenu(const DTO::Menu& menu) {
    auto menus = loadFromDatabase();
    menus.push_back(menu);
    saveToDatabase(menus);
    return true;
}

bool MenuDAO::deleteMenu(uint64_t menuId) {
    auto menus = loadFromDatabase();
    auto it = std::remove_if(menus.begin(), menus.end(),
                             [menuId](const DTO::Menu& menu) {
                                 return menu.menuId == menuId;
                             });
    if (it != menus.end()) {
        menus.erase(it, menus.end());
        saveToDatabase(menus);
        return true;
    }
    return false;
}

bool MenuDAO::updateMenu(const DTO::Menu& menu) {
    auto menus = loadFromDatabase();
    auto it = std::find_if(menus.begin(), menus.end(),
                           [&menu](const DTO::Menu& m) {
                               return m.menuId == menu.menuId;
                           });
    if (it != menus.end()) {
        *it = menu;
        saveToDatabase(menus);
        return true;
    }
    return false;
}

} // namespace DAO
