#pragma once

#include "DTO/DiscardFeedbackAnswer.h"
#include "IDiscardFeedbackAnswerDAO.h"
#include "server/DatabaseConnection.h"

namespace DAO {
class DiscardFeedbackAnswerDAO : public IDiscardFeedbackAnswerDAO {
  std::shared_ptr<DatabaseConnection> dbConnection;

public:
  DiscardFeedbackAnswerDAO();
  bool addAnswer(DTO::DiscardFeedbackAnswer) override;
  bool deleteAnswer(uint64_t answerId) override;
  bool updateAnswer(DTO::DiscardFeedbackAnswer) override;
  DTO::DiscardFeedbackAnswer getAnswerById(uint64_t answerId) override;
  std::vector<DTO::DiscardFeedbackAnswer>
  getAnswersByQuestionId(uint64_t questionId) override;
  std::vector<DTO::DiscardFeedbackAnswer> getAllAnswers() override;
};
}; // namespace DAO