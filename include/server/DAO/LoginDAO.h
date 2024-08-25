#pragma once

#include <vector>
#include "DTO/LoginData.h"

namespace DAO {

class LoginDAO {
public:
    static bool addLogin(const DTO::LoginData& login);
    static bool updateLogoutTime(uint64_t loginId, const std::string& logoutTime);
    static std::vector<DTO::LoginData> getLoginHistoryByUserId(uint64_t userId);
    static void logLoginAttempt(uint64_t userId, uint64_t roleId, const std::string& loginTime);
};

}
