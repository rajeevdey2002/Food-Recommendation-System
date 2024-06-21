#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "Feedback.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace DAO {

class FeedbackDAO {
public:
    static bool addFeedback(const DTO::Feedback& feedback);
    static std::vector<DTO::Feedback> getAllFeedbacks();
    static DTO::Feedback getFeedbackById(uint64_t feedbackId);
    static bool updateFeedback(const DTO::Feedback& feedback);
    static bool deleteFeedback(uint64_t feedbackId);

private:
    static std::string databaseFile;
    static void saveToDatabase(const std::vector<DTO::Feedback>& feedbacks);
    static std::vector<DTO::Feedback> loadFromDatabase();
};

} // namespace DAO
