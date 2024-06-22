#pragma once

#include <vector>
#include "Notification.h"

namespace DAO {

class NotificationDAO {
public:
    static std::vector<DTO::Notification> loadFromDatabase();
    static void saveToDatabase(const std::vector<DTO::Notification>& notifications);
    static bool addNotification(const DTO::Notification& notification);
    static bool deleteNotification(uint64_t notificationId);
    static bool updateNotification(const DTO::Notification& notification);

private:
    static std::vector<DTO::Notification> notifications;
};

}
