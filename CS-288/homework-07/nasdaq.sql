-- drop database for testing purposes only
DROP DATABASE IF EXISTS demo;

CREATE DATABASE demo;

USE demo

CREATE TABLE nasdaq(
  idx INT(10),
  timestamp VARCHAR(22),
  exchange CHAR(6),
  symbol VARCHAR(6),
  company VARCHAR(64),
  volume INT(20),
  price DECIMAL(10, 2),
  percentChange DECIMAL(4, 2),

  PRIMARY KEY (idx)
  -- timestamp is not unique for primary key
);

INSERT INTO nasdaq VALUES("1", "2018-12-04-15-23-50", "Nasdaq", "AMD", "Advanced Micro Devices", "106699859", "21.58", "-2.13");
