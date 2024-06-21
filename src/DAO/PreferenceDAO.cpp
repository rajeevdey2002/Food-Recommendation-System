#include "PreferenceDAO.h"
#include <algorithm>
#include <stdexcept>

namespace DAO {

std::vector<DTO::Preference> PreferenceDAO::preferences;

// Function to load preferences from database
std::vector<DTO::Preference> PreferenceDAO::loadFromDatabase() {
    // Replace with actual database loading logic
    return preferences;
}

// Function to save preferences to database
void PreferenceDAO::saveToDatabase(const std::vector<DTO::Preference>& preferences) {
    // Replace with actual database saving logic
    PreferenceDAO::preferences = preferences;
}

bool PreferenceDAO::addPreference(const DTO::Preference& preference) {
    auto preferences = loadFromDatabase();
    preferences.push_back(preference);
    saveToDatabase(preferences);
    return true;
}

bool PreferenceDAO::deletePreference(uint64_t preferenceId) {
    auto preferences = loadFromDatabase();
    auto it = std::remove_if(preferences.begin(), preferences.end(),
                             [preferenceId](const DTO::Preference& item) {
                                 return item.preferenceId == preferenceId;
                             });
    if (it != preferences.end()) {
        preferences.erase(it, preferences.end());
        saveToDatabase(preferences);
        return true;
    }
    return false;
}

bool PreferenceDAO::updatePreference(const DTO::Preference& preference) {
    auto preferences = loadFromDatabase();
    auto it = std::find_if(preferences.begin(), preferences.end(),
                           [&preference](const DTO::Preference& p) {
                               return p.preferenceId == preference.preferenceId;
                           });
    if (it != preferences.end()) {
        *it = preference;
        saveToDatabase(preferences);
        return true;
    }
    return false;
}

} // namespace DAO
