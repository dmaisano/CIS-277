DROP DATABASE IF EXISTS demo;

CREATE DATABASE demo;

USE demo

CREATE TABLE covid_cases(
  us_state VARCHAR(64) NOT NULL,
  confirmed_cases INT NOT NULL,
  new_cases INT NOT NULL,
  confirmed_deaths INT NOT NULL,
  new_deaths INT NOT NULL,

  PRIMARY KEY(us_state)
);

CREATE TABLE user_preferences(
  ip_addr VARCHAR(32),
  settings TEXT,

  PRIMARY KEY(ip_addr)
)
