#pragma once

#include "DTO/User.h"
#include <vector>

namespace Service {
    class UserService {
    public:
        static bool authenticateUser(int userId, const std::string& password);
    };
}
