#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../include/clientUtilities/ClientDataParser.h"

const std::string validRecommendedFoodData = "STATUS_OK,1,Pasta,12.5,4.3,2,Burger,8.0,3.9";
const std::string invalidRecommendedFoodData = "STATUS_ERROR,1,Pasta,12.5";

const std::string validDailyMenuData = "STATUS_OK,1,Pasta,1,Lunch,12.5,2,Burger,1,Dinner,8.0";
const std::string invalidDailyMenuData = "STATUS_ERROR,1,Pasta,1,Lunch";

const std::string validNotificationData = "STATUS_OK;1,Welcome,2024-08-30;2,Discount,2024-09-01";
const std::string invalidNotificationData = "STATUS_OK;1,Welcome";

const std::string validUserProfileData = "STATUS_OK,123,Vegetarian,Medium,Italian,Yes";
const std::string invalidUserProfileData = "STATUS_ERROR,123,Vegetarian";

const std::string validMenuData = "STATUS_OK,1,Pasta,12.5,2,Burger,8.0";
const std::string invalidMenuData = "STATUS_ERROR,1,Pasta";

const std::string validDeserializeData = "item1,item2,item3";
const std::string invalidDeserializeData = "";

class DataParserTest : public ::testing::Test
{
protected:
    DataParser parser;
};

TEST_F(DataParserTest, ParseRecommendedFood_ValidData)
{
    auto result = parser.parseRecommendedFood(validRecommendedFoodData);
    EXPECT_EQ(result.first, "STATUS_OK");
    EXPECT_EQ(result.second.size(), 2);
    EXPECT_EQ(result.second[0].menuName, "Pasta");
    EXPECT_FLOAT_EQ(result.second[0].price, 12.5);
    EXPECT_FLOAT_EQ(result.second[0].recommendationScore, 4.3);
}

TEST_F(DataParserTest, ParseRecommendedFood_InvalidData)
{
    auto result = parser.parseRecommendedFood(invalidRecommendedFoodData);
    EXPECT_EQ(result.first, "STATUS_ERROR");
    EXPECT_TRUE(result.second.empty());
}

TEST_F(DataParserTest, DeserializeData_ValidData)
{
    auto result = parser.deserializeData(validDeserializeData);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second.size(), 3);
    EXPECT_EQ(result.second[0], "item1");
}

TEST_F(DataParserTest, DeserializeData_InvalidData)
{
    auto result = parser.deserializeData(invalidDeserializeData);
    EXPECT_TRUE(result.first);
    EXPECT_TRUE(result.second.empty());
}

TEST_F(DataParserTest, DeserializeToDailyMenuEntries_ValidData)
{
    auto result = parser.deserializeToDailyMenuEntries(validDailyMenuData);
    EXPECT_EQ(result.first, "STATUS_OK");
    EXPECT_EQ(result.second.size(), 2);
    EXPECT_EQ(result.second[0].itemName, "Pasta");
}

TEST_F(DataParserTest, DeserializeToDailyMenuEntries_InvalidData)
{
    auto result = parser.deserializeToDailyMenuEntries(invalidDailyMenuData);
    EXPECT_EQ(result.first, "STATUS_ERROR");
    EXPECT_TRUE(result.second.empty());
}

TEST_F(DataParserTest, DeserializeUserProfile_ValidData)
{
    auto result = parser.deserializeUserProfile(validUserProfileData);
    EXPECT_EQ(result.first, "STATUS_OK");
    EXPECT_EQ(result.second.userId, 123);
    EXPECT_EQ(result.second.preferenceType, "Vegetarian");
}

TEST_F(DataParserTest, DeserializeMenu_ValidData)
{
    auto result = parser.deserializeMenu(validMenuData);
    EXPECT_EQ(result.first, "STATUS_OK");
    EXPECT_EQ(result.second.size(), 2);
    EXPECT_EQ(result.second[0].menuName, "Pasta");
}

TEST_F(DataParserTest, DeserializeMenu_InvalidData)
{
    auto result = parser.deserializeMenu(invalidMenuData);
    EXPECT_EQ(result.first, "STATUS_ERROR");
    EXPECT_TRUE(result.second.empty());
}
