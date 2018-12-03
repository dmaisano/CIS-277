#!/bin/bash

# does not work with root (tested on ubuntu)

echo "Enter your MySql username"
read mysqlUser

echo "Enter your MySql password"
read mysqlPass

python3 ./nasdaq.py $mysqlUser $mysqlPass
