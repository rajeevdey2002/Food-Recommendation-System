#include "MenuTypeDAO.h"
#include <algorithm>
#include <stdexcept>

namespace DAO {

std::vector<DTO::MenuType> MenuTypeDAO::menuTypes;

std::vector<DTO::MenuType> MenuTypeDAO::loadFromDatabase() {
    return menuTypes;
}

void MenuTypeDAO::saveToDatabase(const std::vector<DTO::MenuType>& menuTypes) {
    MenuTypeDAO::menuTypes = menuTypes;
}

bool MenuTypeDAO::addMenuType(const DTO::MenuType& menuType) {
    auto menuTypes = loadFromDatabase();
    menuTypes.push_back(menuType);
    saveToDatabase(menuTypes);
    return true;
}

bool MenuTypeDAO::deleteMenuType(uint64_t menuTypeId) {
    auto menuTypes = loadFromDatabase();
    auto it = std::remove_if(menuTypes.begin(), menuTypes.end(),
                             [menuTypeId](const DTO::MenuType& item) {
                                 return item.menuTypeId == menuTypeId;
                             });
    if (it != menuTypes.end()) {
        menuTypes.erase(it, menuTypes.end());
        saveToDatabase(menuTypes);
        return true;
    }
    return false;
}

bool MenuTypeDAO::updateMenuType(const DTO::MenuType& menuType) {
    auto menuTypes = loadFromDatabase();
    auto it = std::find_if(menuTypes.begin(), menuTypes.end(),
                           [&menuType](const DTO::MenuType& m) {
                               return m.menuTypeId == menuType.menuTypeId;
                           });
    if (it != menuTypes.end()) {
        *it = menuType;
        saveToDatabase(menuTypes);
        return true;
    }
    return false;
}

}
