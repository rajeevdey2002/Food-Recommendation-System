#include "UserService.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <cppconn/prepared_statement.h>

namespace Service {

bool UserService::authenticateUser(int userId, const std::string& password) {
    try {
        auto db = DatabaseConnection::getInstance();
        auto conn = db->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT password FROM Users WHERE id = ?"));
        pstmt->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            std::string dbPassword = res->getString("password");
            return dbPassword == password;
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error during authentication: " << e.what() << std::endl;
    }
    return false;
}

}
