#include "UserInputHandler.h"
#include <gtest/gtest.h>
#include <sstream>

void setInput(const std::string &input) {
  std::istringstream *iss = new std::istringstream(input);
  std::cin.rdbuf(iss->rdbuf());
}

TEST(UserInputHandlerTest, GetIntInput_ValidInput) {
  setInput("42\n");
  UserInputHandler handler;
  int result = handler.getIntInput("Enter an integer: ");
  EXPECT_EQ(result, 42);
}

TEST(UserInputHandlerTest, GetIntInput_InvalidInput) {
  setInput("abc\n123\n");
  UserInputHandler handler;
  int result = handler.getIntInput("Enter an integer: ");
  EXPECT_EQ(result, 123);
}

TEST(UserInputHandlerTest, GetStringInput_ValidInput) {
  setInput("test_string\n");
  UserInputHandler handler;
  std::string result = handler.getStringInput("Enter a string: ");
  EXPECT_EQ(result, "test_string");
}

TEST(UserInputHandlerTest, GetStringInput_EmptyInput) {
  setInput("\nnon_empty\n");
  UserInputHandler handler;
  std::string result = handler.getStringInput("Enter a string: ");
  EXPECT_EQ(result, "non_empty");
}

TEST(UserInputHandlerTest, GetFoodRatingInput_ValidInput) {
  setInput("4.5\n");
  UserInputHandler handler;
  float result = handler.getFoodRatingInput("Enter a rating: ");
  EXPECT_FLOAT_EQ(result, 4.5);
}

TEST(UserInputHandlerTest, GetFoodRatingInput_InvalidInput) {
  setInput("six\n2.3\n");
  UserInputHandler handler;
  float result = handler.getFoodRatingInput("Enter a rating: ");
  EXPECT_FLOAT_EQ(result, 2.3);
}

TEST(UserInputHandlerTest, GetChoiceInput_ValidInput) {
  setInput("2\n");
  UserInputHandler handler;
  std::vector<std::string> choices = {"Option 1", "Option 2", "Option 3"};
  int result = handler.getChoiceInput("Choose an option: ", choices);
  EXPECT_EQ(result, 2);
}

TEST(UserInputHandlerTest, GetChoiceInput_InvalidInput) {
  setInput("4\n1\n");
  UserInputHandler handler;
  std::vector<std::string> choices = {"Option 1", "Option 2", "Option 3"};
  int result = handler.getChoiceInput("Choose an option: ", choices);
  EXPECT_EQ(result, 1);
}
