#include "NotificationDAO.h"
#include <algorithm>
#include <stdexcept>

namespace DAO {

std::vector<DTO::Notification> NotificationDAO::notifications;

// Function to load notifications from database
std::vector<DTO::Notification> NotificationDAO::loadFromDatabase() {
    // Replace with actual database loading logic
    return notifications;
}

// Function to save notifications to database
void NotificationDAO::saveToDatabase(const std::vector<DTO::Notification>& notifications) {
    // Replace with actual database saving logic
    NotificationDAO::notifications = notifications;
}

bool NotificationDAO::addNotification(const DTO::Notification& notification) {
    auto notifications = loadFromDatabase();
    notifications.push_back(notification);
    saveToDatabase(notifications);
    return true;
}

bool NotificationDAO::deleteNotification(uint64_t notificationId) {
    auto notifications = loadFromDatabase();
    auto it = std::remove_if(notifications.begin(), notifications.end(),
                             [notificationId](const DTO::Notification& item) {
                                 return item.notificationId == notificationId;
                             });
    if (it != notifications.end()) {
        notifications.erase(it, notifications.end());
        saveToDatabase(notifications);
        return true;
    }
    return false;
}

bool NotificationDAO::updateNotification(const DTO::Notification& notification) {
    auto notifications = loadFromDatabase();
    auto it = std::find_if(notifications.begin(), notifications.end(),
                           [&notification](const DTO::Notification& n) {
                               return n.notificationId == notification.notificationId;
                           });
    if (it != notifications.end()) {
        *it = notification;
        saveToDatabase(notifications);
        return true;
    }
    return false;
}

} // namespace DAO
