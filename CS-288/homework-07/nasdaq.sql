-- drop database for testing purposes only
DROP DATABASE IF EXISTS demo;

CREATE DATABASE demo;

USE demo

CREATE TABLE nasdaq(
  timestamp VARCHAR(24),
  exchange CHAR(6),
  symbol VARCHAR(6),
  company VARCHAR(64),
  volume INT(20),
  price DECIMAL(10, 2),
  percentChange DECIMAL(6, 2)
);
