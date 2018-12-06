DROP DATABASE IF EXISTS demo1;

CREATE DATABASE demo1;

USE demo1;

CREATE TABLE book(
    isbn  CHAR(10),
    title VARCHAR(64),
    price DECIMAL(6, 2),

    PRIMARY KEY (isbn)
);

INSERT INTO book(isbn, title, price) VALUES('039957557X', 'Typhoon Fury',       29.00);
INSERT INTO book(isbn, title, price) VALUES('150116340X', 'Sleeping Beauties',  32.50);
INSERT INTO book(isbn, title, price) VALUES('0399593489', 'The Midnight Line',  28.99);
INSERT INTO book(isbn, title, price) VALUES('0385541171', 'The Rooster Bar',    28.95);
INSERT INTO book(isbn, title, price) VALUES('0316225908', 'Two Kinds of Truth', 29.00);
