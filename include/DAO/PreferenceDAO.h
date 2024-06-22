#pragma once

#include <vector>
#include "Preference.h"

namespace DAO {

class PreferenceDAO {
public:
    static std::vector<DTO::Preference> loadFromDatabase();
    static void saveToDatabase(const std::vector<DTO::Preference>& preferences);
    static bool addPreference(const DTO::Preference& preference);
    static bool deletePreference(uint64_t preferenceId);
    static bool updatePreference(const DTO::Preference& preference);

private:
    static std::vector<DTO::Preference> preferences;
};

}
