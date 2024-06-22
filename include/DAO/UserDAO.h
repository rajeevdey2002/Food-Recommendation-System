#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "User.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DAO {

class UserDAO {
public:
    static bool addUser(const DTO::User& user);
    static std::vector<DTO::User> getAllUsers();
    static DTO::User getUserById(uint64_t userId);
    static bool updateUser(const DTO::User& user);
    static bool deleteUser(uint64_t userId);

private:
    static std::string databaseFile;
    static void saveToDatabase(const std::vector<DTO::User>& users);
    static std::vector<DTO::User> loadFromDatabase();
};

}
