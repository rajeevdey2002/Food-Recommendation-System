#pragma once

#include <vector>
#include "../DTO/Login.h"

namespace DAO {

class LoginDAO {
public:
    static bool addLogin(const DTO::Login& login);
    static bool updateLogoutTime(uint64_t loginId, const std::string& logoutTime);
    static std::vector<DTO::Login> getLoginHistoryByUserId(uint64_t userId);
    static void logLoginAttempt(uint64_t userId, uint64_t roleId, const std::string& loginTime);
};

} // namespace DAO
