#include "ScheduledMenuDAO.h"
#include <algorithm>
#include <stdexcept>

namespace DAO {

std::vector<DTO::ScheduledMenu> ScheduledMenuDAO::scheduledMenus;

std::vector<DTO::ScheduledMenu> ScheduledMenuDAO::loadFromDatabase() {
    return scheduledMenus;
}

void ScheduledMenuDAO::saveToDatabase(const std::vector<DTO::ScheduledMenu>& scheduledMenus) {
    ScheduledMenuDAO::scheduledMenus = scheduledMenus;
}

bool ScheduledMenuDAO::addScheduledMenu(const DTO::ScheduledMenu& scheduledMenu) {
    auto scheduledMenus = loadFromDatabase();
    scheduledMenus.push_back(scheduledMenu);
    saveToDatabase(scheduledMenus);
    return true;
}

bool ScheduledMenuDAO::deleteScheduledMenu(uint64_t scheduledMenuId) {
    auto scheduledMenus = loadFromDatabase();
    auto it = std::remove_if(scheduledMenus.begin(), scheduledMenus.end(),
                             [scheduledMenuId](const DTO::ScheduledMenu& item) {
                                 return item.scheduledMenuId == scheduledMenuId;
                             });
    if (it != scheduledMenus.end()) {
        scheduledMenus.erase(it, scheduledMenus.end());
        saveToDatabase(scheduledMenus);
        return true;
    }
    return false;
}

bool ScheduledMenuDAO::updateScheduledMenu(const DTO::ScheduledMenu& scheduledMenu) {
    auto scheduledMenus = loadFromDatabase();
    auto it = std::find_if(scheduledMenus.begin(), scheduledMenus.end(),
                           [&scheduledMenu](const DTO::ScheduledMenu& sm) {
                               return sm.scheduledMenuId == scheduledMenu.scheduledMenuId;
                           });
    if (it != scheduledMenus.end()) {
        *it = scheduledMenu;
        saveToDatabase(scheduledMenus);
        return true;
    }
    return false;
}

}
