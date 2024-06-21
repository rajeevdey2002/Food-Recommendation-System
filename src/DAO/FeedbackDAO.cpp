#include "FeedbackDAO.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace DAO {

std::string FeedbackDAO::databaseFile = "feedbacks.json";

bool FeedbackDAO::addFeedback(const DTO::Feedback& feedback) {
    std::vector<DTO::Feedback> feedbacks = loadFromDatabase();
    feedbacks.push_back(feedback);
    saveToDatabase(feedbacks);
    return true;
}

std::vector<DTO::Feedback> FeedbackDAO::getAllFeedbacks() {
    return loadFromDatabase();
}

DTO::Feedback FeedbackDAO::getFeedbackById(uint64_t feedbackId) {
    std::vector<DTO::Feedback> feedbacks = loadFromDatabase();
    for (const auto& feedback : feedbacks) {
        if (feedback.feedbackId == feedbackId) {
            return feedback;
        }
    }
    throw std::runtime_error("Feedback not found");
}

bool FeedbackDAO::updateFeedback(const DTO::Feedback& feedback) {
    std::vector<DTO::Feedback> feedbacks = loadFromDatabase();
    for (auto& fb : feedbacks) {
        if (fb.feedbackId == feedback.feedbackId) {
            fb = feedback;
            saveToDatabase(feedbacks);
            return true;
        }
    }
    return false;
}

bool FeedbackDAO::deleteFeedback(uint64_t feedbackId) {
    std::vector<DTO::Feedback> feedbacks = loadFromDatabase();
    
    // Loop through the vector and find the feedback with the given id
    auto it = feedbacks.begin();
    while (it != feedbacks.end()) {
        if (it->feedbackId == feedbackId) {
            it = feedbacks.erase(it);  // Erase the element and get the next iterator
        } else {
            ++it;  // Move to the next element
        }
    }

    // Save the modified vector back to the database
    saveToDatabase(feedbacks);
    return true;
}

void FeedbackDAO::saveToDatabase(const std::vector<DTO::Feedback>& feedbacks) {
    std::ofstream file(databaseFile);
    rapidjson::Document doc;
    doc.SetArray();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    for (const auto& feedback : feedbacks) {
        rapidjson::Value feedbackObj(rapidjson::kObjectType);
        feedbackObj.AddMember("feedbackId", feedback.feedbackId, allocator);
        feedbackObj.AddMember("userId", feedback.userId, allocator);
        feedbackObj.AddMember("menuId", feedback.menuId, allocator);
        feedbackObj.AddMember("foodItemId", feedback.foodItemId, allocator);
        feedbackObj.AddMember("rating", feedback.rating, allocator);
        feedbackObj.AddMember("comment", rapidjson::Value(feedback.comment.c_str(), allocator).Move(), allocator);
        feedbackObj.AddMember("date", rapidjson::Value(feedback.date.c_str(), allocator).Move(), allocator);
        doc.PushBack(feedbackObj, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    file << buffer.GetString();
}

std::vector<DTO::Feedback> FeedbackDAO::loadFromDatabase() {
    std::ifstream file(databaseFile);
    if (!file.is_open()) {
        return {};
    }

    rapidjson::IStreamWrapper isw(file);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    std::vector<DTO::Feedback> feedbacks;
    for (const auto& item : doc.GetArray()) {
        uint64_t feedbackId = item["feedbackId"].GetUint64();
        uint64_t userId = item["userId"].GetUint64();
        uint64_t menuId = item["menuId"].GetUint64();
        uint64_t foodItemId = item["foodItemId"].GetUint64();
        uint32_t rating = item["rating"].GetUint();
        std::string comment = item["comment"].GetString();
        std::string date = item["date"].GetString();
        feedbacks.emplace_back(feedbackId, userId, menuId, foodItemId, rating, comment, date);
    }

    return feedbacks;
}

} // namespace DAO
