#include "LoginService.h"
#include "../DAO/LoginDAO.h"
#include "../DatabaseConnection.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <memory>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

namespace Service {

bool LoginService::loginUser(uint64_t userId, const std::string& password) {
    uint64_t roleId;
    try {
        auto db = DatabaseConnection::getInstance();
        auto conn = db->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT roleId, password FROM User WHERE userId = ?"));
        pstmt->setUInt64(1, userId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        
        if (res->next()) {
            std::string dbPassword = res->getString("password");
            if (dbPassword != password) {
                std::cerr << "Invalid password." << std::endl;
                return false;
            }
            roleId = res->getUInt64("roleId");
        } else {
            std::cerr << "User ID not found." << std::endl;
            return false;
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching user details: " << e.what() << std::endl;
        return false;
    }

    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
    std::string loginTime = ss.str();

    DTO::Login login(0, userId, roleId, loginTime, "");
    if (DAO::LoginDAO::addLogin(login)) {
        DAO::LoginDAO::logLoginAttempt(userId, roleId, loginTime);
        return true;
    } else {
        return false;
    }
}

bool LoginService::logoutUser(uint64_t loginId) {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
    std::string logoutTime = ss.str();

    return DAO::LoginDAO::updateLogoutTime(loginId, logoutTime);
}

std::vector<DTO::Login> LoginService::getUserLoginHistory(uint64_t userId) {
    return DAO::LoginDAO::getLoginHistoryByUserId(userId);
}

}
