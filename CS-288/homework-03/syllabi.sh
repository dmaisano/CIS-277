#!/bin/bash

# permissions cheat sheet
# 0 – no permission
# 1 – execute
# 2 – write
# 3 – write and execute
# 4 – read
# 5 – read and execute
# 6 – read and write
# 7 – read, write, and execute

# cd to home dir
cd ~

# mkdir if none exists
mkdir -p NJIT

# change directories
cd ./NJIT

# create dirs
mkdir -p ./CHM ./ECO ./PHY ./PHY/PHYS

# recursively set '750' permission for every dir
chmod -R 750 ~/NJIT

# create the files in their respective directories
touch ./CHM/chm104 ./CHM/chm203 ./ECO/eco102 ./PHY/phy102 ./PHY/phy104 ./PHY/PHYS/phys430

# changes all the permissions of the files
find ~/NJIT -type f -exec chmod 640 {} \;
