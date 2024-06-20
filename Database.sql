-- Drop the existing database if it exists
DROP DATABASE IF EXISTS tempDatabase;

-- Create a new database
CREATE DATABASE tempDatabase;

-- Use the new database
USE tempDatabase;

-- Create tables
CREATE TABLE Users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL
);

CREATE TABLE Feedback (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    feedback TEXT,
    FOREIGN KEY (user_id) REFERENCES Users(id)
);

-- Insert data into Users table
INSERT INTO Users (name, email) VALUES ('Alice', 'alice@example.com');
INSERT INTO Users (name, email) VALUES ('Bob', 'bob@example.com');
INSERT INTO Users (name, email) VALUES ('Charlie', 'charlie@example.com');
INSERT INTO Users (name, email) VALUES ('David', 'david@example.com');
INSERT INTO Users (name, email) VALUES ('Eva', 'eva@example.com');
INSERT INTO Users (name, email) VALUES ('Frank', 'frank@example.com');
INSERT INTO Users (name, email) VALUES ('Grace', 'grace@example.com');
INSERT INTO Users (name, email) VALUES ('Hannah', 'hannah@example.com');
INSERT INTO Users (name, email) VALUES ('Isaac', 'isaac@example.com');
INSERT INTO Users (name, email) VALUES ('Jack', 'jack@example.com');

-- Insert data into Feedback table
INSERT INTO Feedback (user_id, feedback) VALUES (1, 'Great service!');
INSERT INTO Feedback (user_id, feedback) VALUES (2, 'Very satisfied.');
INSERT INTO Feedback (user_id, feedback) VALUES (3, 'Could be better.');
INSERT INTO Feedback (user_id, feedback) VALUES (4, 'Awesome experience.');
INSERT INTO Feedback (user_id, feedback) VALUES (5, 'Good customer support.');
INSERT INTO Feedback (user_id, feedback) VALUES (6, 'Will recommend to others.');
INSERT INTO Feedback (user_id, feedback) VALUES (7, 'Average service.');
INSERT INTO Feedback (user_id, feedback) VALUES (8, 'Very professional.');
INSERT INTO Feedback (user_id, feedback) VALUES (9, 'Quick response time.');
INSERT INTO Feedback (user_id, feedback) VALUES (10, 'Satisfied with the service.');
