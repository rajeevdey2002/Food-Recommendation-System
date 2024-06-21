#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "../DTO/Login.h"

namespace Service {

class LoginService {
public:
    static bool loginUser(uint64_t userId, const std::string& password);
    static bool logoutUser(uint64_t loginId);
    static std::vector<DTO::Login> getUserLoginHistory(uint64_t userId);
};

} // namespace Service
