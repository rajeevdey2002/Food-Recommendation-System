#include "LoginDAO.h"
#include "../DatabaseConnection.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>

namespace DAO {

bool LoginDAO::addLogin(const DTO::Login& login) {
    try {
        auto db = DatabaseConnection::getInstance();
        auto conn = db->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO Login (userId, roleId, loginTime, logoutTime) VALUES (?, ?, ?, ?)"
        ));
        pstmt->setUInt64(1, login.userId);
        pstmt->setUInt64(2, login.roleId);
        pstmt->setString(3, login.loginTime);
        pstmt->setNull(4, sql::DataType::TIMESTAMP);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error adding login: " << e.what() << std::endl;
        return false;
    }
}

bool LoginDAO::updateLogoutTime(uint64_t loginId, const std::string& logoutTime) {
    try {
        auto db = DatabaseConnection::getInstance();
        auto conn = db->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "UPDATE Login SET logoutTime = ? WHERE loginId = ?"
        ));
        pstmt->setString(1, logoutTime);
        pstmt->setUInt64(2, loginId);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error updating logout time: " << e.what() << std::endl;
        return false;
    }
}

std::vector<DTO::Login> LoginDAO::getLoginHistoryByUserId(uint64_t userId) {
    std::vector<DTO::Login> loginHistory;
    try {
        auto db = DatabaseConnection::getInstance();
        auto conn = db->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "SELECT id, userId, roleId, loginTime, logoutTime FROM Login WHERE userId = ?"
        ));
        pstmt->setUInt64(1, userId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            DTO::Login login(
                res->getUInt64("id"),
                res->getUInt64("userId"),
                res->getUInt64("roleId"),
                res->getString("loginTime"),
                res->getString("logoutTime")
            );
            loginHistory.push_back(login);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching login history: " << e.what() << std::endl;
    }
    return loginHistory;
}

void LoginDAO::logLoginAttempt(uint64_t userId, uint64_t roleId, const std::string& loginTime) {
    try {
        auto db = DatabaseConnection::getInstance();
        auto conn = db->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO Login (userId, roleId, loginTime, logoutTime) VALUES (?, ?, ?, ?)"
        ));
        pstmt->setUInt64(1, userId);
        pstmt->setUInt64(2, roleId);
        pstmt->setString(3, loginTime);
        pstmt->setNull(4, sql::DataType::TIMESTAMP);
        pstmt->executeUpdate();
    } catch (sql::SQLException &e) {
        std::cerr << "Error logging login attempt: " << e.what() << std::endl;
    }
}

}
