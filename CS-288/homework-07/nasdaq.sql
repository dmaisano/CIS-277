DROP DATABASE IF EXISTS demo;

CREATE DATABASE demo;

USE demo

CREATE TABLE book(
  isbn  CHAR(10),
  title VARCHAR(64),
  price DECIMAL(6, 2),

  PRIMARY KEY (isbn)
);
