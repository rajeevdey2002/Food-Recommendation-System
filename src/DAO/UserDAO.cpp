#include "UserDAO.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace DAO {

std::string UserDAO::databaseFile = "users.json";

bool UserDAO::addUser(const DTO::User& user) {
    std::vector<DTO::User> users = loadFromDatabase();
    users.push_back(user);
    saveToDatabase(users);
    return true;
}

std::vector<DTO::User> UserDAO::getAllUsers() {
    return loadFromDatabase();
}

DTO::User UserDAO::getUserById(uint64_t userId) {
    std::vector<DTO::User> users = loadFromDatabase();
    for (const auto& user : users) {
        if (user.userId == userId) {
            return user;
        }
    }
    throw std::runtime_error("User not found");
}

bool UserDAO::updateUser(const DTO::User& user) {
    std::vector<DTO::User> users = loadFromDatabase();
    for (auto& u : users) {
        if (u.userId == user.userId) {
            u = user;
            saveToDatabase(users);
            return true;
        }
    }
    return false;
}

bool UserDAO::deleteUser(uint64_t userId) {
    std::vector<DTO::User> users = loadFromDatabase();
    
    auto it = users.begin();
    while (it != users.end()) {
        if (it->userId == userId) {
            it = users.erase(it);
        } else {
            ++it;
        }
    }

    saveToDatabase(users);
    return true;
}

void UserDAO::saveToDatabase(const std::vector<DTO::User>& users) {
    std::ofstream file(databaseFile);
    rapidjson::Document doc;
    doc.SetArray();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    for (const auto& user : users) {
        rapidjson::Value userObj(rapidjson::kObjectType);
        userObj.AddMember("userId", user.userId, allocator);
        userObj.AddMember("name", rapidjson::Value(user.name.c_str(), allocator).Move(), allocator);
        userObj.AddMember("password", rapidjson::Value(user.password.c_str(), allocator).Move(), allocator);
        userObj.AddMember("roleId", user.roleId, allocator);
        userObj.AddMember("lastNotificationId", user.lastNotificationId, allocator);
        doc.PushBack(userObj, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    file << buffer.GetString();
}

std::vector<DTO::User> UserDAO::loadFromDatabase() {
    std::ifstream file(databaseFile);
    if (!file.is_open()) {
        return {};
    }

    rapidjson::IStreamWrapper isw(file);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    std::vector<DTO::User> users;
    for (const auto& item : doc.GetArray()) {
        uint64_t userId = item["userId"].GetUint64();
        std::string name = item["name"].GetString();
        std::string password = item["password"].GetString();
        uint64_t roleId = item["roleId"].GetUint64();
        uint64_t lastNotificationId = item["lastNotificationId"].GetUint64();
        users.emplace_back(userId, name, password, roleId, lastNotificationId);
    }

    return users;
}

}
