-- Drop the existing database if it exists
DROP DATABASE IF EXISTS tempDatabase;

-- Create a new database
CREATE DATABASE tempDatabase;

-- Use the new database
USE tempDatabase;

-- Create tables
CREATE TABLE Role (
    id INT AUTO_INCREMENT PRIMARY KEY,
    roleName VARCHAR(100) NOT NULL
);

CREATE TABLE User (
    userId INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    password VARCHAR(255) NOT NULL,
    roleId INT,
    lastNotificationId INT,
    FOREIGN KEY (roleId) REFERENCES Role(id)
);

CREATE TABLE Feedback (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    feedback TEXT,
    FOREIGN KEY (user_id) REFERENCES User(userId)
);

CREATE TABLE FoodItem (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    description TEXT
);

CREATE TABLE FoodItemType (
    id INT AUTO_INCREMENT PRIMARY KEY,
    typeName VARCHAR(100) NOT NULL
);

CREATE TABLE Menu (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    description TEXT
);

CREATE TABLE MenuItem (
    id INT AUTO_INCREMENT PRIMARY KEY,
    menuId INT,
    foodItemId INT,
    FOREIGN KEY (menuId) REFERENCES Menu(id),
    FOREIGN KEY (foodItemId) REFERENCES FoodItem(id)
);

CREATE TABLE MenuType (
    id INT AUTO_INCREMENT PRIMARY KEY,
    typeName VARCHAR(100) NOT NULL
);

CREATE TABLE Notification (
    id INT AUTO_INCREMENT PRIMARY KEY,
    userId INT,
    message TEXT NOT NULL,
    isRead BOOLEAN DEFAULT FALSE,
    createdAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (userId) REFERENCES User(userId)
);

CREATE TABLE Preference (
    id INT AUTO_INCREMENT PRIMARY KEY,
    userId INT,
    preferenceKey VARCHAR(100) NOT NULL,
    preferenceValue VARCHAR(100) NOT NULL,
    FOREIGN KEY (userId) REFERENCES User(userId)
);

CREATE TABLE ScheduledMenu (
    id INT AUTO_INCREMENT PRIMARY KEY,
    menuId INT,
    scheduledDate DATE NOT NULL,
    FOREIGN KEY (menuId) REFERENCES Menu(id)
);

CREATE TABLE Login (
    loginId INT AUTO_INCREMENT PRIMARY KEY,
    userId INT,
    roleId INT,
    loginTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    logoutTime TIMESTAMP NULL,
    FOREIGN KEY (userId) REFERENCES User(userId),
    FOREIGN KEY (roleId) REFERENCES Role(id)
);

-- Insert data into Role table
INSERT INTO Role (roleName) VALUES ('Admin'), ('User'), ('Chef');

-- Insert data into User table
INSERT INTO User (name, password, roleId, lastNotificationId) VALUES 
    ('Alice', 'alice123', 1, 0),
    ('Bob', 'bob123', 2, 0),
    ('Charlie', 'charlie123', 3, 0);

-- Insert data into Feedback table
INSERT INTO Feedback (user_id, feedback) VALUES 
    (1, 'Great service!'),
    (2, 'Very satisfied.'),
    (3, 'Could be better.'),
    (1, 'Awesome experience.'),
    (2, 'Good customer support.'),
    (3, 'Will recommend to others.'),
    (1, 'Average service.'),
    (2, 'Very professional.'),
    (3, 'Quick response time.'),
    (1, 'Satisfied with the service.');

-- Insert data into FoodItem table
INSERT INTO FoodItem (name, price, description) VALUES 
    ('Burger', 5.99, 'A delicious beef burger with lettuce, tomato, and cheese.'),
    ('Pizza', 8.99, 'Cheesy pizza with a variety of toppings.'),
    ('Pasta', 7.99, 'Pasta with marinara sauce and parmesan cheese.'),
    ('Salad', 4.99, 'Fresh garden salad with a choice of dressings.'),
    ('Soda', 1.99, 'Chilled soda with a variety of flavors.');

-- Insert data into FoodItemType table
INSERT INTO FoodItemType (typeName) VALUES ('Vegetarian'), ('Non-Vegetarian');

-- Insert data into Menu table
INSERT INTO Menu (name, description) VALUES 
    ('Breakfast Menu', 'Morning meals and beverages'),
    ('Lunch Menu', 'Afternoon meals and beverages'),
    ('Dinner Menu', 'Evening meals and beverages');

-- Insert data into MenuItem table
INSERT INTO MenuItem (menuId, foodItemId) VALUES 
    (1, 1), (1, 2),
    (2, 3), (2, 4),
    (3, 5), (3, 1);

-- Insert data into MenuType table
INSERT INTO MenuType (typeName) VALUES ('Breakfast'), ('Lunch'), ('Dinner');

-- Insert data into Notification table
INSERT INTO Notification (userId, message, isRead) VALUES 
    (1, 'Your order is ready for pickup.', FALSE),
    (2, 'Your table reservation is confirmed.', FALSE),
    (3, 'New items have been added to the menu.', TRUE),
    (1, 'Your feedback has been received.', TRUE),
    (2, 'Special discounts available this weekend.', FALSE);

-- Insert data into Preference table
INSERT INTO Preference (userId, preferenceKey, preferenceValue) VALUES 
    (1, 'Diet', 'Vegetarian'),
    (2, 'Spice Level', 'Medium'),
    (3, 'Diet', 'Vegan'),
    (1, 'Allergies', 'Peanuts'),
    (2, 'Cuisine', 'Italian');

-- Insert data into ScheduledMenu table
INSERT INTO ScheduledMenu (menuId, scheduledDate) VALUES 
    (1, '2024-06-21'),
    (2, '2024-06-22'),
    (3, '2024-06-23');

-- Insert data into Login table
INSERT INTO Login (userId, roleId) VALUES 
    (1, 1), -- User with ID 1, role Admin
    (2, 2), -- User with ID 2, role Chef
    (3, 3); -- User with ID 3, role Employee
