-- MySQL dump 10.13  Distrib 8.0.39, for Linux (x86_64)
--
-- Host: localhost    Database: recommendationEngine
-- ------------------------------------------------------
-- Server version	8.0.39-0ubuntu0.22.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `FeedbackAnswer`
--

DROP TABLE IF EXISTS `FeedbackAnswer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `FeedbackAnswer` (
  `answer_id` int NOT NULL AUTO_INCREMENT,
  `question_id` int DEFAULT NULL,
  `menuId` int DEFAULT NULL,
  `userId` int DEFAULT NULL,
  `answer_text` text,
  `answer_date` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`answer_id`),
  KEY `question_id` (`question_id`),
  KEY `menuId` (`menuId`),
  KEY `userId` (`userId`),
  CONSTRAINT `FeedbackAnswer_ibfk_1` FOREIGN KEY (`question_id`) REFERENCES `FeedbackQuestion` (`question_id`) ON DELETE SET NULL,
  CONSTRAINT `FeedbackAnswer_ibfk_2` FOREIGN KEY (`menuId`) REFERENCES `menu` (`menuId`) ON DELETE SET NULL,
  CONSTRAINT `FeedbackAnswer_ibfk_3` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `FeedbackAnswer`
--

LOCK TABLES `FeedbackAnswer` WRITE;
/*!40000 ALTER TABLE `FeedbackAnswer` DISABLE KEYS */;
INSERT INTO `FeedbackAnswer` VALUES (1,1,NULL,3,'everything','2024-07-27 17:55:17'),(2,2,NULL,3,'good','2024-07-27 17:55:17'),(3,3,NULL,3,'nope','2024-07-27 17:55:17'),(4,1,NULL,16,'price','2024-07-30 08:54:34'),(5,2,NULL,16,'more spicy','2024-07-30 08:54:34'),(6,3,NULL,16,'not interested','2024-07-30 08:54:34'),(7,1,NULL,16,'dfgfd','2024-07-30 08:57:23'),(8,2,NULL,16,'gfd','2024-07-30 08:57:23'),(9,3,NULL,16,'gfd','2024-07-30 08:57:23'),(10,NULL,NULL,16,'fd','2024-07-30 08:57:23'),(11,1,38,3,'taste','2024-08-05 17:04:57'),(12,2,38,3,'little spicy','2024-08-05 17:04:57'),(13,3,38,3,'nooo','2024-08-05 17:04:57'),(14,5,38,3,'no','2024-08-05 17:04:57');
/*!40000 ALTER TABLE `FeedbackAnswer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `FeedbackQuestion`
--

DROP TABLE IF EXISTS `FeedbackQuestion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `FeedbackQuestion` (
  `question_id` int NOT NULL AUTO_INCREMENT,
  `question_text` varchar(255) NOT NULL,
  PRIMARY KEY (`question_id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `FeedbackQuestion`
--

LOCK TABLES `FeedbackQuestion` WRITE;
/*!40000 ALTER TABLE `FeedbackQuestion` DISABLE KEYS */;
INSERT INTO `FeedbackQuestion` VALUES (1,'What didn’t you like about food'),(2,'How would you like this food to taste?'),(3,'hare your mom’s recipe.'),(5,'is menu is value for money?');
/*!40000 ALTER TABLE `FeedbackQuestion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dailyMenu`
--

DROP TABLE IF EXISTS `dailyMenu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `dailyMenu` (
  `dailyMenuId` int NOT NULL AUTO_INCREMENT,
  `menuId` int DEFAULT NULL,
  `availability` int DEFAULT NULL,
  `mealCategory` enum('breakfast','lunch','dinner') DEFAULT NULL,
  `menuDate` date DEFAULT NULL,
  PRIMARY KEY (`dailyMenuId`),
  UNIQUE KEY `menuId` (`menuId`,`menuDate`,`mealCategory`),
  CONSTRAINT `fk_menuId` FOREIGN KEY (`menuId`) REFERENCES `menu` (`menuId`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=54 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dailyMenu`
--

LOCK TABLES `dailyMenu` WRITE;
/*!40000 ALTER TABLE `dailyMenu` DISABLE KEYS */;
INSERT INTO `dailyMenu` VALUES (1,NULL,1,'lunch','2024-07-01'),(2,NULL,1,'dinner','2024-07-01'),(3,NULL,1,'lunch','2024-06-30'),(4,NULL,1,'dinner','2024-07-02'),(5,NULL,1,'dinner','2024-07-02'),(6,NULL,1,'breakfast','2024-07-02'),(7,NULL,1,'lunch','2024-07-02'),(9,NULL,1,'breakfast','2024-07-02'),(10,NULL,1,'breakfast','2024-07-02'),(11,NULL,1,'lunch','2024-07-03'),(12,NULL,1,'lunch','2024-07-03'),(13,NULL,1,'dinner','2024-07-03'),(14,NULL,1,'breakfast','2024-07-03'),(15,NULL,1,'breakfast','2024-07-06'),(16,NULL,1,'lunch','2024-07-06'),(17,NULL,1,'dinner','2024-07-06'),(18,NULL,1,'lunch','2024-07-06'),(19,NULL,1,'dinner','2024-07-07'),(21,NULL,1,'lunch','2024-07-07'),(22,NULL,1,'dinner','2024-07-08'),(23,NULL,1,'breakfast','2024-07-08'),(24,NULL,1,'breakfast','2024-07-08'),(25,NULL,1,'dinner','2024-07-17'),(26,NULL,1,'lunch','2024-07-17'),(27,NULL,0,'lunch','2024-07-20'),(28,NULL,0,'lunch','2024-07-20'),(30,NULL,1,'breakfast','2024-07-22'),(31,NULL,1,'breakfast','2024-07-27'),(32,NULL,1,'lunch','2024-07-27'),(33,NULL,1,'dinner','2024-07-30'),(34,NULL,1,'breakfast','2024-07-30'),(35,NULL,1,'breakfast','2024-07-30'),(36,NULL,1,'lunch','2024-07-30'),(37,NULL,1,'dinner','2024-08-03'),(38,NULL,1,'breakfast','2024-08-03'),(39,NULL,1,'lunch','2024-08-03'),(40,NULL,1,'breakfast','2024-08-03'),(41,NULL,1,'breakfast','2024-08-03'),(42,NULL,1,'breakfast','2024-08-03'),(43,NULL,1,'breakfast','2024-08-03'),(44,36,1,'breakfast','2024-08-03'),(45,31,1,'breakfast','2024-08-04'),(46,35,1,'lunch','2024-08-04'),(47,40,1,'dinner','2024-08-04'),(48,38,1,'dinner','2024-08-04'),(49,38,1,'dinner','2024-08-05'),(51,43,1,'dinner','2024-08-05'),(52,40,1,'dinner','2024-08-05'),(53,44,1,'lunch','2024-08-05');
/*!40000 ALTER TABLE `dailyMenu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `feedback`
--

DROP TABLE IF EXISTS `feedback`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `feedback` (
  `feedback_id` int NOT NULL AUTO_INCREMENT,
  `menuId` int NOT NULL,
  `userId` int NOT NULL,
  `rating` float NOT NULL,
  `comment` text,
  `feedback_date` date DEFAULT NULL,
  PRIMARY KEY (`feedback_id`),
  KEY `userId` (`userId`),
  KEY `menuId` (`menuId`),
  CONSTRAINT `feedback_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`),
  CONSTRAINT `feedback_chk_1` CHECK ((`rating` between 1.0 and 5.0))
) ENGINE=InnoDB AUTO_INCREMENT=295 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `feedback`
--

LOCK TABLES `feedback` WRITE;
/*!40000 ALTER TABLE `feedback` DISABLE KEYS */;
INSERT INTO `feedback` VALUES (1,27,13,4.5,'Delicious and spicy!','2024-07-21'),(2,27,14,4,'Nice flavor!','2024-07-24'),(3,27,15,3.5,'Could be spicier.','2024-07-24'),(4,27,16,5,'Perfect snack!','2024-07-10'),(5,27,17,4.5,'Very tasty!','2024-08-02'),(6,27,18,4,'Well prepared.','2024-07-09'),(7,27,19,4.5,'Authentic taste.','2024-08-01'),(8,27,20,4,'Good but spicy.','2024-07-07'),(9,27,21,4.5,'Highly recommended!','2024-07-24'),(10,27,22,5,'Absolutely delicious!','2024-08-02'),(11,27,13,3.5,'Average taste.','2024-07-28'),(12,27,14,4,'Good snack!','2024-07-07'),(13,27,15,4.5,'Loved it!','2024-08-03'),(14,27,16,4,'Well made.','2024-07-22'),(15,27,17,5,'Perfect balance of flavors!','2024-08-01'),(16,28,13,5,'Authentic taste!','2024-07-30'),(17,28,14,4.5,'Loved it!','2024-07-17'),(18,28,15,4,'Very flavorful.','2024-07-21'),(19,28,16,4.5,'Well cooked.','2024-07-19'),(20,28,17,4,'Tasty biryani.','2024-07-25'),(21,28,18,4.5,'Great spices!','2024-08-04'),(22,28,19,5,'Amazing taste!','2024-08-01'),(23,28,20,4,'Nice and spicy.','2024-07-19'),(24,28,21,4.5,'Highly recommended!','2024-07-25'),(25,28,22,5,'Absolutely delicious!','2024-07-31'),(26,28,13,4,'Nice biryani.','2024-07-14'),(27,28,14,4.5,'Great flavor.','2024-07-30'),(28,28,15,4,'Good spices.','2024-07-16'),(29,28,16,5,'Perfectly cooked!','2024-07-12'),(30,28,17,4.5,'Very tasty!','2024-07-06'),(31,29,13,4,'Loved the flavors!','2024-07-20'),(32,29,14,4.5,'Very tasty!','2024-07-14'),(33,29,15,4,'Nice taste.','2024-07-08'),(34,29,16,4,'Good veg option.','2024-07-22'),(35,29,17,4.5,'Well cooked.','2024-07-18'),(36,29,18,4,'Tasty veg biryani.','2024-07-19'),(37,29,19,4.5,'Great spices.','2024-07-08'),(38,29,20,4,'Nice flavors.','2024-08-04'),(39,29,21,4.5,'Highly recommended!','2024-07-25'),(40,29,22,4,'Good biryani.','2024-07-14'),(41,29,13,4.5,'Delicious!','2024-07-21'),(42,29,14,4,'Tasty and flavorful.','2024-07-26'),(43,29,15,4.5,'Loved it.','2024-07-31'),(44,29,16,4,'Good taste.','2024-07-14'),(45,29,17,4.5,'Perfect balance.','2024-07-30'),(46,30,13,4.5,'Perfectly cooked!','2024-07-13'),(47,30,14,4,'Nice and tender.','2024-07-31'),(48,30,15,4.5,'Great taste.','2024-07-19'),(49,30,16,4,'Tasty kabab.','2024-07-29'),(50,30,17,4.5,'Well seasoned.','2024-07-20'),(51,30,18,4,'Delicious.','2024-07-09'),(52,30,19,4.5,'Very tasty.','2024-07-09'),(53,30,20,4,'Loved the flavor.','2024-07-13'),(54,30,21,4.5,'Highly recommended!','2024-08-01'),(55,30,22,5,'Absolutely delicious!','2024-07-26'),(56,30,13,4,'Nice kabab.','2024-07-30'),(57,30,14,4.5,'Great flavor.','2024-08-03'),(58,30,15,4,'Good taste.','2024-07-17'),(59,30,16,5,'Perfectly cooked!','2024-08-03'),(60,30,17,4.5,'Very tasty!','2024-07-26'),(61,31,13,4,'Very refreshing!','2024-07-23'),(62,31,14,4.5,'Great taste!','2024-07-31'),(63,31,15,4,'Nice flavor.','2024-07-21'),(64,31,16,4,'Good dessert.','2024-07-07'),(65,31,17,4.5,'Well prepared.','2024-07-26'),(66,31,18,4,'Tasty!','2024-07-14'),(67,31,19,4.5,'Very refreshing.','2024-07-16'),(68,31,20,4,'Nice dessert.','2024-08-01'),(69,31,21,4.5,'Highly recommended!','2024-07-16'),(70,31,22,5,'Absolutely delicious!','2024-07-11'),(71,31,13,4,'Nice and sweet.','2024-07-31'),(72,31,14,4.5,'Great flavor.','2024-07-27'),(73,31,15,4,'Good taste.','2024-08-04'),(74,31,16,5,'Perfect dessert!','2024-07-28'),(75,31,17,4.5,'Very tasty!','2024-08-01'),(76,32,13,4.5,'Great taste!','2024-07-10'),(77,32,14,4,'Nice and tender.','2024-07-06'),(78,32,15,4.5,'Very tasty.','2024-07-27'),(79,32,16,4,'Loved it.','2024-07-21'),(80,32,17,4.5,'Well seasoned.','2024-07-18'),(81,32,18,4,'Delicious.','2024-07-21'),(82,32,19,4.5,'Very flavorful.','2024-07-14'),(83,32,20,4,'Nice flavor.','2024-08-02'),(84,32,21,4.5,'Highly recommended!','2024-07-27'),(85,32,22,5,'Absolutely delicious!','2024-07-30'),(86,32,13,4,'Nice dish.','2024-08-01'),(87,32,14,4.5,'Great taste.','2024-07-07'),(88,32,15,4,'Good spices.','2024-07-23'),(89,32,16,5,'Perfectly cooked!','2024-07-29'),(90,32,17,4.5,'Very tasty!','2024-07-12'),(91,33,13,4.5,'Nicely spiced!','2024-07-26'),(92,33,14,4,'Good taste.','2024-07-28'),(93,33,15,4.5,'Very flavorful.','2024-07-27'),(94,33,16,4,'Nice dish.','2024-07-15'),(95,33,17,4.5,'Well cooked.','2024-07-18'),(96,33,18,4,'Delicious.','2024-07-09'),(97,33,19,4.5,'Very tasty.','2024-07-17'),(98,33,20,4,'Nice spices.','2024-07-20'),(99,33,21,4.5,'Highly recommended!','2024-07-14'),(100,33,22,5,'Absolutely delicious!','2024-07-07'),(101,33,13,4,'Nicely spiced.','2024-07-14'),(102,33,14,4.5,'Great taste.','2024-07-17'),(103,33,15,4,'Good dish.','2024-08-04'),(104,33,16,5,'Perfect spices!','2024-07-28'),(105,33,17,4.5,'Very tasty!','2024-08-01'),(106,34,13,4.5,'Soft and tasty!','2024-07-10'),(107,34,14,4,'Nice and soft.','2024-07-06'),(108,34,15,4.5,'Very delicious.','2024-07-26'),(109,34,16,4,'Loved the texture.','2024-07-16'),(110,34,17,4.5,'Well prepared.','2024-07-27'),(111,34,18,4,'Tasty.','2024-07-21'),(112,34,19,4.5,'Very soft.','2024-07-19'),(113,34,20,4,'Nice texture.','2024-07-27'),(114,34,21,4.5,'Highly recommended!','2024-07-13'),(115,34,22,5,'Absolutely delicious!','2024-07-08'),(116,34,13,4,'Nice and soft.','2024-07-27'),(117,34,14,4.5,'Great taste.','2024-07-14'),(118,34,15,4,'Good texture.','2024-07-13'),(119,34,16,5,'Perfectly cooked!','2024-07-19'),(120,34,17,4.5,'Very tasty!','2024-07-18'),(121,35,13,4,'Loved the sweetness!','2024-07-28'),(122,35,14,4.5,'Very tasty!','2024-07-21'),(123,35,15,4,'Nice and sweet.','2024-07-15'),(124,35,16,4,'Good dessert.','2024-07-07'),(125,35,17,4.5,'Well made.','2024-07-16'),(126,35,18,4,'Tasty!','2024-07-23'),(127,35,19,4.5,'Very sweet.','2024-07-30'),(128,35,20,4,'Nice dessert.','2024-07-16'),(129,35,21,4.5,'Highly recommended!','2024-07-14'),(130,35,22,5,'Absolutely delicious!','2024-07-15'),(131,35,13,4,'Nice and sweet.','2024-07-30'),(132,35,14,4.5,'Great flavor.','2024-07-10'),(133,35,15,4,'Good dessert.','2024-07-15'),(134,35,16,5,'Perfect sweetness!','2024-07-09'),(135,35,17,4.5,'Very tasty!','2024-07-23'),(136,36,13,4.5,'Great combination!','2024-07-23'),(137,36,14,4,'Nice taste.','2024-07-11'),(138,36,15,4.5,'Very delicious.','2024-07-12'),(139,36,16,4,'Loved it.','2024-07-20'),(140,36,17,4.5,'Well prepared.','2024-07-30'),(141,36,18,4,'Tasty.','2024-07-24'),(142,36,19,4.5,'Very nice.','2024-07-23'),(143,36,20,4,'Good taste.','2024-07-10'),(144,36,21,4.5,'Highly recommended!','2024-08-03'),(145,36,22,5,'Absolutely delicious!','2024-07-13'),(146,36,13,4,'Nice combination.','2024-07-20'),(147,36,14,4.5,'Great taste.','2024-07-26'),(148,36,15,4,'Good dish.','2024-08-03'),(149,36,16,5,'Perfectly prepared!','2024-07-27'),(150,36,17,4.5,'Very tasty!','2024-07-26'),(151,38,13,4.5,'Delicious, perfect blend of spices.','2024-08-05'),(152,38,14,4,'Tasty and creamy.','2024-08-05'),(153,38,15,4.8,'Best butter chicken I\'ve had!','2024-08-05'),(154,38,16,4.2,'Rich and flavorful.','2024-08-05'),(155,38,17,4.6,'Absolutely delicious.','2024-08-05'),(156,38,18,4.1,'Great taste, will order again.','2024-08-05'),(157,38,19,4.3,'Very good, just a bit too spicy.','2024-08-05'),(158,38,20,4.7,'Perfectly cooked, amazing sauce.','2024-08-05'),(159,38,21,4.4,'Loved the flavors.','2024-08-05'),(160,38,22,4.9,'Outstanding butter chicken.','2024-08-05'),(162,38,13,4.5,'Perfectly balanced flavors.','2024-08-05'),(163,38,14,4.8,'Delicious and creamy.','2024-08-05'),(164,38,15,4.2,'Great taste, just right.','2024-08-05'),(165,38,16,4.6,'Loved every bite.','2024-08-05'),(166,38,17,4.3,'Perfectly cooked.','2024-08-05'),(167,39,13,4.5,'Very tasty fish curry.','2024-08-05'),(168,39,14,4.2,'Perfectly cooked fish.','2024-08-05'),(169,39,15,4.8,'Best fish curry I\'ve had!','2024-08-05'),(170,39,16,4.1,'Loved the flavors.','2024-08-05'),(171,39,17,4.4,'Delicious and well-seasoned.','2024-08-05'),(172,39,18,4,'Tasty, but a bit too spicy.','2024-08-05'),(173,39,19,4.3,'Very good fish curry.','2024-08-05'),(174,39,20,4.7,'Perfectly balanced flavors.','2024-08-05'),(175,39,21,4.6,'Amazing fish curry!','2024-08-05'),(176,39,22,4.1,'Loved the taste.','2024-08-05'),(178,39,13,4.8,'Very delicious fish curry.','2024-08-05'),(179,39,14,4.2,'Great taste, will order again.','2024-08-05'),(180,39,15,4.6,'Loved every bite.','2024-08-05'),(181,39,16,4.3,'Perfectly balanced spices.','2024-08-05'),(182,39,17,4,'Good, but a bit too salty.','2024-08-05'),(183,40,13,4.8,'Best mutton curry I\'ve had!','2024-08-05'),(184,40,14,4.6,'Rich and flavorful.','2024-08-05'),(185,40,15,4.5,'Absolutely delicious.','2024-08-05'),(186,40,16,4.3,'Great taste, will order again.','2024-08-05'),(187,40,17,4.7,'Very tasty and well-cooked.','2024-08-05'),(188,40,18,4.1,'Loved the spices.','2024-08-05'),(189,40,19,4.4,'Amazing flavor and texture.','2024-08-05'),(190,40,20,4.9,'Outstanding mutton curry.','2024-08-05'),(191,40,21,4.2,'Very good, just a bit too spicy.','2024-08-05'),(192,40,22,4.5,'Perfectly cooked and seasoned.','2024-08-05'),(194,40,13,4.8,'Rich and creamy.','2024-08-05'),(195,40,14,4.6,'Delicious and spicy.','2024-08-05'),(196,40,15,4.3,'Perfectly cooked mutton.','2024-08-05'),(197,40,16,4.5,'Loved the flavors.','2024-08-05'),(198,40,17,4.2,'Great taste, just right.','2024-08-05'),(199,43,13,4.2,'Good, but a bit too sweet.','2024-08-05'),(200,43,14,4.5,'Perfectly sweet and soft.','2024-08-05'),(201,43,15,4.3,'Loved the texture.','2024-08-05'),(202,43,16,4.6,'Delicious and well-made.','2024-08-05'),(203,43,17,4.1,'Great taste, will order again.','2024-08-05'),(204,43,18,4.4,'Very good, just a bit too sweet.','2024-08-05'),(205,43,19,4.2,'Loved the flavors.','2024-08-05'),(206,43,20,4.5,'Perfectly balanced sweetness.','2024-08-05'),(207,43,21,4.3,'Amazing taste, just right.','2024-08-05'),(208,43,22,4.6,'Soft and sweet, loved it.','2024-08-05'),(210,43,13,4.5,'Perfectly made.','2024-08-05'),(211,43,14,4.8,'Loved the sweetness.','2024-08-05'),(212,43,15,4.3,'Delicious and soft.','2024-08-05'),(213,43,16,4.6,'Very tasty and well-made.','2024-08-05'),(214,43,17,4.2,'Great taste, will order again.','2024-08-05'),(215,44,13,4.5,'Perfectly creamy and sweet.','2024-08-05'),(216,44,14,4.7,'Best kheer I\'ve had!','2024-08-05'),(217,44,15,4.6,'Delicious and well-made.','2024-08-05'),(218,44,16,4.4,'Great taste, will order again.','2024-08-05'),(219,44,17,4.1,'Loved the flavors.','2024-08-05'),(220,44,18,4.3,'Very tasty and creamy.','2024-08-05'),(221,44,19,4.5,'Perfectly balanced sweetness.','2024-08-05'),(222,44,20,4.7,'Outstanding kheer.','2024-08-05'),(223,44,21,4.6,'Very good, just a bit too sweet.','2024-08-05'),(224,44,22,4.3,'Loved the texture.','2024-08-05'),(226,44,13,4.8,'Amazing flavors.','2024-08-05'),(227,44,14,4.6,'Loved every bite.','2024-08-05'),(228,44,15,4.4,'Very tasty and creamy.','2024-08-05'),(229,44,16,4.7,'Perfectly made.','2024-08-05'),(230,44,17,4.2,'Great taste, will order again.','2024-08-05'),(231,45,13,4.1,'A bit too sweet for my taste.','2024-08-05'),(232,45,14,4.4,'Perfectly crispy and sweet.','2024-08-05'),(233,45,15,4.3,'Loved the crunchiness.','2024-08-05'),(234,45,16,4.6,'Delicious and well-made.','2024-08-05'),(235,45,17,4.1,'Great taste, will order again.','2024-08-05'),(236,45,18,4.4,'Very good, just a bit too sweet.','2024-08-05'),(237,45,19,4.2,'Loved the flavors.','2024-08-05'),(238,45,20,4.5,'Perfectly balanced sweetness.','2024-08-05'),(239,45,21,4.3,'Amazing taste, just right.','2024-08-05'),(240,45,22,4.6,'Crispy and sweet, loved it.','2024-08-05'),(242,45,13,4.5,'Perfectly made.','2024-08-05'),(243,45,14,4.8,'Loved the sweetness.','2024-08-05'),(244,45,15,4.3,'Delicious and crispy.','2024-08-05'),(245,45,16,4.6,'Very tasty and well-made.','2024-08-05'),(246,45,17,4.2,'Great taste, will order again.','2024-08-05'),(247,37,13,2,'Too oily.','2024-08-05'),(248,37,14,1.5,'Lacked flavor.','2024-08-05'),(249,37,15,2.3,'Not authentic taste.','2024-08-05'),(250,37,16,1.8,'Too spicy.','2024-08-05'),(251,37,17,2.1,'Not fresh.','2024-08-05'),(252,37,18,1.9,'Bland taste.','2024-08-05'),(253,37,19,2.2,'Undercooked bhature.','2024-08-05'),(254,37,20,1.7,'Overcooked chole.','2024-08-05'),(255,37,21,2.4,'Not worth the price.','2024-08-05'),(256,37,22,2,'Disappointed.','2024-08-05'),(258,37,13,2.1,'Not good.','2024-08-05'),(259,37,14,1.9,'Too greasy.','2024-08-05'),(260,37,15,2.3,'Disappointing.','2024-08-05'),(261,37,16,2,'Not fresh.','2024-08-05'),(262,37,17,1.8,'Poor quality.','2024-08-05'),(263,41,13,2,'Too spicy.','2024-08-05'),(264,41,14,1.5,'Overcooked.','2024-08-05'),(265,41,15,2.3,'Too dry.','2024-08-05'),(266,41,16,1.8,'Not flavorful.','2024-08-05'),(267,41,17,2.1,'Bad texture.','2024-08-05'),(268,41,18,1.9,'Too salty.','2024-08-05'),(269,41,19,2.2,'Overfried.','2024-08-05'),(270,41,20,1.7,'Undercooked.','2024-08-05'),(271,41,21,2.4,'Not worth the price.','2024-08-05'),(272,41,22,2,'Disappointing.','2024-08-05'),(274,41,13,2.1,'Too greasy.','2024-08-05'),(275,41,14,1.9,'Bland taste.','2024-08-05'),(276,41,15,2.3,'Too spicy.','2024-08-05'),(277,41,16,2,'Overcooked.','2024-08-05'),(278,41,17,1.8,'Poor quality.','2024-08-05'),(279,42,13,2,'Too spicy.','2024-08-05'),(280,42,14,1.5,'Overcooked.','2024-08-05'),(281,42,15,2.3,'Too dry.','2024-08-05'),(282,42,16,1.8,'Not flavorful.','2024-08-05'),(283,42,17,2.1,'Bad texture.','2024-08-05'),(284,42,18,1.9,'Too salty.','2024-08-05'),(285,42,19,2.2,'Overcooked.','2024-08-05'),(286,42,20,1.7,'Undercooked.','2024-08-05'),(287,42,21,2.4,'Not worth the price.','2024-08-05'),(288,42,22,2,'Disappointing.','2024-08-05'),(290,42,13,2.1,'Too greasy.','2024-08-05'),(291,42,14,1.9,'Bland taste.','2024-08-05'),(292,42,15,2.3,'Too spicy.','2024-08-05'),(293,42,16,2,'Overcooked.','2024-08-05'),(294,42,17,1.8,'Poor quality.','2024-08-05');
/*!40000 ALTER TABLE `feedback` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `menu`
--

DROP TABLE IF EXISTS `menu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `menu` (
  `menuId` int NOT NULL AUTO_INCREMENT,
  `menu_name` varchar(40) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `diet_type` enum('Vegetarian','Non Vegetarian','Eggetarian') DEFAULT NULL,
  `spice_level` enum('High','Medium','Low','None') DEFAULT NULL,
  `cuisine_type` enum('North Indian','South Indian','Other') DEFAULT NULL,
  `sweet_type` enum('Yes','No') DEFAULT NULL,
  PRIMARY KEY (`menuId`),
  UNIQUE KEY `menu_name` (`menu_name`)
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `menu`
--

LOCK TABLES `menu` WRITE;
/*!40000 ALTER TABLE `menu` DISABLE KEYS */;
INSERT INTO `menu` VALUES (27,'vada pav',15.00,'Vegetarian','High','North Indian','No'),(28,'Biriyani',140.00,'Non Vegetarian','Medium','South Indian','No'),(29,'Veg Biriyani',80.00,'Vegetarian','Medium','South Indian','No'),(30,'kabab',60.00,'Non Vegetarian','Medium','South Indian','No'),(31,'mango juice',40.00,'Vegetarian','None','Other','Yes'),(32,'egg rice',50.00,'Eggetarian','Medium','Other','No'),(33,'lemon rice',40.00,'Vegetarian','Medium','South Indian','No'),(34,'idli vada',40.00,'Vegetarian','None','South Indian','No'),(35,'rice sambar',40.00,'Vegetarian','Medium','South Indian','No'),(36,'pani puri',25.00,'Vegetarian','High','North Indian','No'),(37,'chole bhature',60.00,'Vegetarian','Medium','North Indian','No'),(38,'butter chicken',120.00,'Non Vegetarian','Medium','North Indian','No'),(39,'fish curry',100.00,'Non Vegetarian','High','South Indian','No'),(40,'mutton curry',150.00,'Non Vegetarian','High','North Indian','No'),(41,'chicken 65',90.00,'Non Vegetarian','High','South Indian','No'),(42,'prawn masala',130.00,'Non Vegetarian','Medium','South Indian','No'),(43,'gulab jamun',30.00,'Vegetarian','None','North Indian','Yes'),(44,'kheer',35.00,'Vegetarian','None','North Indian','Yes'),(45,'jalebi',20.00,'Vegetarian','None','North Indian','Yes');
/*!40000 ALTER TABLE `menu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `notification`
--

DROP TABLE IF EXISTS `notification`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `notification` (
  `notificationId` int NOT NULL AUTO_INCREMENT,
  `message` text NOT NULL,
  `dateUpdated` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`notificationId`)
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `notification`
--

LOCK TABLES `notification` WRITE;
/*!40000 ALTER TABLE `notification` DISABLE KEYS */;
INSERT INTO `notification` VALUES (1,'Menu is added','2024-07-06 07:13:10'),(2,'Menu is added','2024-07-06 09:48:25'),(3,'Menu is added','2024-07-06 11:58:22'),(4,'Menu is added','2024-07-06 11:58:52'),(5,'Menu is added','2024-07-07 08:23:24'),(6,'Menu is added','2024-07-07 08:31:00'),(7,'Menu is rolled out','2024-07-07 19:03:40'),(8,'Menu is rolled out','2024-07-07 19:20:29'),(9,'Menu is rolled out','2024-07-07 19:20:58'),(10,'Menu is rolled out','2024-07-17 10:06:03'),(11,'Menu is rolled out','2024-07-17 10:07:12'),(12,'Menu is rolled out','2024-07-20 09:10:40'),(13,'Menu is rolled out','2024-07-20 15:57:52'),(14,'Menu is rolled out','2024-07-22 16:49:31'),(15,'Menu is rolled out','2024-07-27 17:42:03'),(16,'Menu is rolled out','2024-07-27 17:42:14'),(17,'Menu is rolled out','2024-07-30 08:49:10'),(18,'Menu is rolled out','2024-07-30 08:49:55'),(19,'Menu is rolled out','2024-07-30 09:00:06'),(20,'Menu is rolled out','2024-07-30 09:00:19'),(21,'Menu is rolled out','2024-08-03 07:49:07'),(22,'Menu is rolled out','2024-08-03 07:49:39'),(23,'Menu is rolled out','2024-08-03 07:52:32'),(24,'Menu is rolled out','2024-08-03 07:52:40'),(25,'Menu is rolled out','2024-08-03 07:52:54'),(26,'Menu is rolled out','2024-08-03 08:17:23'),(27,'Menu is rolled out','2024-08-03 08:17:40'),(28,'Menu is rolled out','2024-08-03 16:12:25'),(29,'Menu is rolled out','2024-08-04 16:31:14'),(30,'Menu is rolled out','2024-08-04 16:31:28'),(31,'Menu is rolled out','2024-08-04 16:31:40'),(32,'Menu is rolled out','2024-08-04 16:32:06'),(33,'Menu is rolled out','2024-08-05 16:51:38'),(34,'Menu is rolled out','2024-08-05 16:58:04'),(35,'Menu is rolled out','2024-08-05 16:58:15'),(36,'Menu is rolled out','2024-08-05 16:58:33');
/*!40000 ALTER TABLE `notification` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `userNotificationStatus`
--

DROP TABLE IF EXISTS `userNotificationStatus`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `userNotificationStatus` (
  `userId` int NOT NULL,
  `notificationId` int NOT NULL,
  `viewedStatus` enum('not_viewed','viewed') DEFAULT 'not_viewed',
  PRIMARY KEY (`userId`,`notificationId`),
  KEY `notificationId` (`notificationId`),
  CONSTRAINT `userNotificationStatus_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`),
  CONSTRAINT `userNotificationStatus_ibfk_2` FOREIGN KEY (`notificationId`) REFERENCES `notification` (`notificationId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userNotificationStatus`
--

LOCK TABLES `userNotificationStatus` WRITE;
/*!40000 ALTER TABLE `userNotificationStatus` DISABLE KEYS */;
INSERT INTO `userNotificationStatus` VALUES (1,2,'not_viewed'),(1,3,'not_viewed'),(1,4,'not_viewed'),(1,5,'not_viewed'),(1,6,'not_viewed'),(1,7,'not_viewed'),(1,8,'not_viewed'),(1,9,'not_viewed'),(1,10,'not_viewed'),(1,11,'not_viewed'),(1,12,'not_viewed'),(1,13,'not_viewed'),(1,14,'not_viewed'),(1,15,'not_viewed'),(1,16,'not_viewed'),(1,17,'not_viewed'),(1,18,'not_viewed'),(1,19,'not_viewed'),(1,20,'not_viewed'),(1,21,'not_viewed'),(1,22,'not_viewed'),(1,23,'not_viewed'),(1,24,'not_viewed'),(1,25,'not_viewed'),(1,26,'not_viewed'),(1,27,'not_viewed'),(1,28,'not_viewed'),(1,29,'not_viewed'),(1,30,'not_viewed'),(1,31,'not_viewed'),(1,32,'not_viewed'),(1,33,'not_viewed'),(1,34,'not_viewed'),(1,35,'not_viewed'),(1,36,'not_viewed'),(2,2,'not_viewed'),(2,3,'not_viewed'),(2,4,'not_viewed'),(2,5,'not_viewed'),(2,6,'not_viewed'),(2,7,'not_viewed'),(2,8,'not_viewed'),(2,9,'not_viewed'),(2,10,'not_viewed'),(2,11,'not_viewed'),(2,12,'not_viewed'),(2,13,'not_viewed'),(2,14,'not_viewed'),(2,15,'not_viewed'),(2,16,'not_viewed'),(2,17,'not_viewed'),(2,18,'not_viewed'),(2,19,'not_viewed'),(2,20,'not_viewed'),(2,21,'not_viewed'),(2,22,'not_viewed'),(2,23,'not_viewed'),(2,24,'not_viewed'),(2,25,'not_viewed'),(2,26,'not_viewed'),(2,27,'not_viewed'),(2,28,'not_viewed'),(2,29,'not_viewed'),(2,30,'not_viewed'),(2,31,'not_viewed'),(2,32,'not_viewed'),(2,33,'not_viewed'),(2,34,'not_viewed'),(2,35,'not_viewed'),(2,36,'not_viewed'),(3,2,'viewed'),(3,3,'viewed'),(3,4,'viewed'),(3,5,'viewed'),(3,6,'viewed'),(3,7,'viewed'),(3,8,'viewed'),(3,9,'viewed'),(3,10,'viewed'),(3,11,'viewed'),(3,12,'viewed'),(3,13,'viewed'),(3,14,'not_viewed'),(3,15,'not_viewed'),(3,16,'not_viewed'),(3,17,'not_viewed'),(3,18,'not_viewed'),(3,19,'not_viewed'),(3,20,'not_viewed'),(3,21,'not_viewed'),(3,22,'not_viewed'),(3,23,'not_viewed'),(3,24,'not_viewed'),(3,25,'not_viewed'),(3,26,'not_viewed'),(3,27,'not_viewed'),(3,28,'not_viewed'),(3,29,'not_viewed'),(3,30,'not_viewed'),(3,31,'not_viewed'),(3,32,'not_viewed'),(3,33,'not_viewed'),(3,34,'not_viewed'),(3,35,'not_viewed'),(3,36,'not_viewed'),(4,2,'not_viewed'),(4,3,'not_viewed'),(4,4,'not_viewed'),(4,5,'not_viewed'),(4,6,'not_viewed'),(4,7,'not_viewed'),(4,8,'not_viewed'),(4,9,'not_viewed'),(4,10,'not_viewed'),(4,11,'not_viewed'),(4,12,'not_viewed'),(4,13,'not_viewed'),(4,14,'not_viewed'),(4,15,'not_viewed'),(4,16,'not_viewed'),(4,17,'not_viewed'),(4,18,'not_viewed'),(4,19,'not_viewed'),(4,20,'not_viewed'),(4,21,'not_viewed'),(4,22,'not_viewed'),(4,23,'not_viewed'),(4,24,'not_viewed'),(4,25,'not_viewed'),(4,26,'not_viewed'),(4,27,'not_viewed'),(4,28,'not_viewed'),(4,29,'not_viewed'),(4,30,'not_viewed'),(4,31,'not_viewed'),(4,32,'not_viewed'),(4,33,'not_viewed'),(4,34,'not_viewed'),(4,35,'not_viewed'),(4,36,'not_viewed'),(13,2,'not_viewed'),(13,3,'not_viewed'),(13,4,'not_viewed'),(13,5,'not_viewed'),(13,6,'not_viewed'),(13,7,'not_viewed'),(13,8,'not_viewed'),(13,9,'not_viewed'),(13,10,'not_viewed'),(13,11,'not_viewed'),(13,12,'not_viewed'),(13,13,'not_viewed'),(13,14,'not_viewed'),(13,15,'not_viewed'),(13,16,'not_viewed'),(13,17,'not_viewed'),(13,18,'not_viewed'),(13,19,'not_viewed'),(13,20,'not_viewed'),(13,21,'not_viewed'),(13,22,'not_viewed'),(13,23,'not_viewed'),(13,24,'not_viewed'),(13,25,'not_viewed'),(13,26,'not_viewed'),(13,27,'not_viewed'),(13,28,'not_viewed'),(13,29,'not_viewed'),(13,30,'not_viewed'),(13,31,'not_viewed'),(13,32,'not_viewed'),(13,33,'not_viewed'),(13,34,'not_viewed'),(13,35,'not_viewed'),(13,36,'not_viewed'),(14,2,'not_viewed'),(14,3,'not_viewed'),(14,4,'not_viewed'),(14,5,'not_viewed'),(14,6,'not_viewed'),(14,7,'not_viewed'),(14,8,'not_viewed'),(14,9,'not_viewed'),(14,10,'not_viewed'),(14,11,'not_viewed'),(14,12,'not_viewed'),(14,13,'not_viewed'),(14,14,'not_viewed'),(14,15,'not_viewed'),(14,16,'not_viewed'),(14,17,'not_viewed'),(14,18,'not_viewed'),(14,19,'not_viewed'),(14,20,'not_viewed'),(14,21,'not_viewed'),(14,22,'not_viewed'),(14,23,'not_viewed'),(14,24,'not_viewed'),(14,25,'not_viewed'),(14,26,'not_viewed'),(14,27,'not_viewed'),(14,28,'not_viewed'),(14,29,'not_viewed'),(14,30,'not_viewed'),(14,31,'not_viewed'),(14,32,'not_viewed'),(14,33,'not_viewed'),(14,34,'not_viewed'),(14,35,'not_viewed'),(14,36,'not_viewed'),(15,2,'not_viewed'),(15,3,'not_viewed'),(15,4,'not_viewed'),(15,5,'not_viewed'),(15,6,'not_viewed'),(15,7,'not_viewed'),(15,8,'not_viewed'),(15,9,'not_viewed'),(15,10,'not_viewed'),(15,11,'not_viewed'),(15,12,'not_viewed'),(15,13,'not_viewed'),(15,14,'not_viewed'),(15,15,'not_viewed'),(15,16,'not_viewed'),(15,17,'not_viewed'),(15,18,'not_viewed'),(15,19,'not_viewed'),(15,20,'not_viewed'),(15,21,'not_viewed'),(15,22,'not_viewed'),(15,23,'not_viewed'),(15,24,'not_viewed'),(15,25,'not_viewed'),(15,26,'not_viewed'),(15,27,'not_viewed'),(15,28,'not_viewed'),(15,29,'not_viewed'),(15,30,'not_viewed'),(15,31,'not_viewed'),(15,32,'not_viewed'),(15,33,'not_viewed'),(15,34,'not_viewed'),(15,35,'not_viewed'),(15,36,'not_viewed'),(16,2,'viewed'),(16,3,'viewed'),(16,4,'viewed'),(16,5,'viewed'),(16,6,'viewed'),(16,7,'viewed'),(16,8,'viewed'),(16,9,'viewed'),(16,10,'viewed'),(16,11,'viewed'),(16,12,'viewed'),(16,13,'viewed'),(16,14,'viewed'),(16,15,'viewed'),(16,16,'viewed'),(16,17,'viewed'),(16,18,'not_viewed'),(16,19,'not_viewed'),(16,20,'not_viewed'),(16,21,'not_viewed'),(16,22,'not_viewed'),(16,23,'not_viewed'),(16,24,'not_viewed'),(16,25,'not_viewed'),(16,26,'not_viewed'),(16,27,'not_viewed'),(16,28,'not_viewed'),(16,29,'not_viewed'),(16,30,'not_viewed'),(16,31,'not_viewed'),(16,32,'not_viewed'),(16,33,'not_viewed'),(16,34,'not_viewed'),(16,35,'not_viewed'),(16,36,'not_viewed'),(17,2,'not_viewed'),(17,3,'not_viewed'),(17,4,'not_viewed'),(17,5,'not_viewed'),(17,6,'not_viewed'),(17,7,'not_viewed'),(17,8,'not_viewed'),(17,9,'not_viewed'),(17,10,'not_viewed'),(17,11,'not_viewed'),(17,12,'not_viewed'),(17,13,'not_viewed'),(17,14,'not_viewed'),(17,15,'not_viewed'),(17,16,'not_viewed'),(17,17,'not_viewed'),(17,18,'not_viewed'),(17,19,'not_viewed'),(17,20,'not_viewed'),(17,21,'not_viewed'),(17,22,'not_viewed'),(17,23,'not_viewed'),(17,24,'not_viewed'),(17,25,'not_viewed'),(17,26,'not_viewed'),(17,27,'not_viewed'),(17,28,'not_viewed'),(17,29,'not_viewed'),(17,30,'not_viewed'),(17,31,'not_viewed'),(17,32,'not_viewed'),(17,33,'not_viewed'),(17,34,'not_viewed'),(17,35,'not_viewed'),(17,36,'not_viewed'),(18,2,'not_viewed'),(18,3,'not_viewed'),(18,4,'not_viewed'),(18,5,'not_viewed'),(18,6,'not_viewed'),(18,7,'not_viewed'),(18,8,'not_viewed'),(18,9,'not_viewed'),(18,10,'not_viewed'),(18,11,'not_viewed'),(18,12,'not_viewed'),(18,13,'not_viewed'),(18,14,'not_viewed'),(18,15,'not_viewed'),(18,16,'not_viewed'),(18,17,'not_viewed'),(18,18,'not_viewed'),(18,19,'not_viewed'),(18,20,'not_viewed'),(18,21,'not_viewed'),(18,22,'not_viewed'),(18,23,'not_viewed'),(18,24,'not_viewed'),(18,25,'not_viewed'),(18,26,'not_viewed'),(18,27,'not_viewed'),(18,28,'not_viewed'),(18,29,'not_viewed'),(18,30,'not_viewed'),(18,31,'not_viewed'),(18,32,'not_viewed'),(18,33,'not_viewed'),(18,34,'not_viewed'),(18,35,'not_viewed'),(18,36,'not_viewed'),(19,2,'not_viewed'),(19,3,'not_viewed'),(19,4,'not_viewed'),(19,5,'not_viewed'),(19,6,'not_viewed'),(19,7,'not_viewed'),(19,8,'not_viewed'),(19,9,'not_viewed'),(19,10,'not_viewed'),(19,11,'not_viewed'),(19,12,'not_viewed'),(19,13,'not_viewed'),(19,14,'not_viewed'),(19,15,'not_viewed'),(19,16,'not_viewed'),(19,17,'not_viewed'),(19,18,'not_viewed'),(19,19,'not_viewed'),(19,20,'not_viewed'),(19,21,'not_viewed'),(19,22,'not_viewed'),(19,23,'not_viewed'),(19,24,'not_viewed'),(19,25,'not_viewed'),(19,26,'not_viewed'),(19,27,'not_viewed'),(19,28,'not_viewed'),(19,29,'not_viewed'),(19,30,'not_viewed'),(19,31,'not_viewed'),(19,32,'not_viewed'),(19,33,'not_viewed'),(19,34,'not_viewed'),(19,35,'not_viewed'),(19,36,'not_viewed'),(20,2,'not_viewed'),(20,3,'not_viewed'),(20,4,'not_viewed'),(20,5,'not_viewed'),(20,6,'not_viewed'),(20,7,'not_viewed'),(20,8,'not_viewed'),(20,9,'not_viewed'),(20,10,'not_viewed'),(20,11,'not_viewed'),(20,12,'not_viewed'),(20,13,'not_viewed'),(20,14,'not_viewed'),(20,15,'not_viewed'),(20,16,'not_viewed'),(20,17,'not_viewed'),(20,18,'not_viewed'),(20,19,'not_viewed'),(20,20,'not_viewed'),(20,21,'not_viewed'),(20,22,'not_viewed'),(20,23,'not_viewed'),(20,24,'not_viewed'),(20,25,'not_viewed'),(20,26,'not_viewed'),(20,27,'not_viewed'),(20,28,'not_viewed'),(20,29,'not_viewed'),(20,30,'not_viewed'),(20,31,'not_viewed'),(20,32,'not_viewed'),(20,33,'not_viewed'),(20,34,'not_viewed'),(20,35,'not_viewed'),(20,36,'not_viewed'),(21,2,'not_viewed'),(21,3,'not_viewed'),(21,4,'not_viewed'),(21,5,'not_viewed'),(21,6,'not_viewed'),(21,7,'not_viewed'),(21,8,'not_viewed'),(21,9,'not_viewed'),(21,10,'not_viewed'),(21,11,'not_viewed'),(21,12,'not_viewed'),(21,13,'not_viewed'),(21,14,'not_viewed'),(21,15,'not_viewed'),(21,16,'not_viewed'),(21,17,'not_viewed'),(21,18,'not_viewed'),(21,19,'not_viewed'),(21,20,'not_viewed'),(21,21,'not_viewed'),(21,22,'not_viewed'),(21,23,'not_viewed'),(21,24,'not_viewed'),(21,25,'not_viewed'),(21,26,'not_viewed'),(21,27,'not_viewed'),(21,28,'not_viewed'),(21,29,'not_viewed'),(21,30,'not_viewed'),(21,31,'not_viewed'),(21,32,'not_viewed'),(21,33,'not_viewed'),(21,34,'not_viewed'),(21,35,'not_viewed'),(21,36,'not_viewed'),(22,2,'not_viewed'),(22,3,'not_viewed'),(22,4,'not_viewed'),(22,5,'not_viewed'),(22,6,'not_viewed'),(22,7,'not_viewed'),(22,8,'not_viewed'),(22,9,'not_viewed'),(22,10,'not_viewed'),(22,11,'not_viewed'),(22,12,'not_viewed'),(22,13,'not_viewed'),(22,14,'not_viewed'),(22,15,'not_viewed'),(22,16,'not_viewed'),(22,17,'not_viewed'),(22,18,'not_viewed'),(22,19,'not_viewed'),(22,20,'not_viewed'),(22,21,'not_viewed'),(22,22,'not_viewed'),(22,23,'not_viewed'),(22,24,'not_viewed'),(22,25,'not_viewed'),(22,26,'not_viewed'),(22,27,'not_viewed'),(22,28,'not_viewed'),(22,29,'not_viewed'),(22,30,'not_viewed'),(22,31,'not_viewed'),(22,32,'not_viewed'),(22,33,'not_viewed'),(22,34,'not_viewed'),(22,35,'not_viewed'),(22,36,'not_viewed');
/*!40000 ALTER TABLE `userNotificationStatus` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `userOrder`
--

DROP TABLE IF EXISTS `userOrder`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `userOrder` (
  `orderId` int NOT NULL AUTO_INCREMENT,
  `userId` int DEFAULT NULL,
  `dailyMenuId` int DEFAULT NULL,
  `orderTimestamp` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`orderId`),
  KEY `userId` (`userId`),
  KEY `dailyMenuId` (`dailyMenuId`),
  CONSTRAINT `userOrder_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`),
  CONSTRAINT `userOrder_ibfk_2` FOREIGN KEY (`dailyMenuId`) REFERENCES `dailyMenu` (`dailyMenuId`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userOrder`
--

LOCK TABLES `userOrder` WRITE;
/*!40000 ALTER TABLE `userOrder` DISABLE KEYS */;
INSERT INTO `userOrder` VALUES (1,3,4,'2024-07-02 17:33:38'),(2,3,21,'2024-07-07 18:07:06'),(3,16,33,'2024-07-30 08:50:13'),(4,3,49,'2024-08-05 17:03:44');
/*!40000 ALTER TABLE `userOrder` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `userId` int NOT NULL AUTO_INCREMENT,
  `name` varchar(40) NOT NULL,
  `role` enum('ADMIN','CHEF','EMPLOYEE') NOT NULL,
  `password` varchar(64) NOT NULL,
  `preferenceType` enum('No Preference','Vegetarian','Non Vegetarian','Eggetarian') DEFAULT 'No Preference',
  `spiceLevel` enum('No Preference','High','Medium','Low') DEFAULT 'No Preference',
  `cuisinePreference` enum('No Preference','North Indian','South Indian','Other') DEFAULT 'No Preference',
  `sweetTooth` enum('No Preference','Yes','No') DEFAULT 'No Preference',
  PRIMARY KEY (`userId`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'John Doe','ADMIN','admin123','Non Vegetarian','Medium','South Indian','No'),(2,'Jane Smith','CHEF','chef456','Non Vegetarian','No Preference','North Indian','No'),(3,'Alice Johnson','EMPLOYEE','emp789','Non Vegetarian','Medium','South Indian','Yes'),(4,'Bob Williams','EMPLOYEE','emp234','Vegetarian','Medium','North Indian','No'),(13,'Amit Patel','CHEF','amit456','Non Vegetarian','High','North Indian','No'),(14,'Sunita Rao','EMPLOYEE','sunita789','No Preference','High','No Preference','No'),(15,'Rajesh Kumar','ADMIN','rajesh123','Eggetarian','Medium','North Indian','Yes'),(16,'Anjali Sharma','EMPLOYEE','anjali234','Vegetarian','High','South Indian','No'),(17,'Vikram Singh','CHEF','vikram456','Vegetarian','No Preference','No Preference','Yes'),(18,'Priya Nair','EMPLOYEE','priya789','Vegetarian','Medium','North Indian','Yes'),(19,'Ravi Verma','ADMIN','ravi123','No Preference','High','Other','No Preference'),(20,'Kavita Mehta','EMPLOYEE','kavita234','No Preference','Low','South Indian','Yes'),(21,'Suresh Desai','CHEF','suresh456','Eggetarian','Low','No Preference','No'),(22,'Meera Gupta','EMPLOYEE','meera789','Vegetarian','Low','No Preference','Yes');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-08-29 11:41:55
