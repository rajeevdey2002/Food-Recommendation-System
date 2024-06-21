#pragma once

#include <vector>
#include "ScheduledMenu.h"

namespace DAO {

class ScheduledMenuDAO {
public:
    static std::vector<DTO::ScheduledMenu> loadFromDatabase();
    static void saveToDatabase(const std::vector<DTO::ScheduledMenu>& scheduledMenus);
    static bool addScheduledMenu(const DTO::ScheduledMenu& scheduledMenu);
    static bool deleteScheduledMenu(uint64_t scheduledMenuId);
    static bool updateScheduledMenu(const DTO::ScheduledMenu& scheduledMenu);

private:
    static std::vector<DTO::ScheduledMenu> scheduledMenus;
};

} // namespace DAO
