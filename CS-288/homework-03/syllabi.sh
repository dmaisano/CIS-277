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

# create sub-directories
mkdir -p NJIT/CHM NJIT/ECO NJIT/PHY/PHYS

# create the text files per subdirectory
touch NJIT/CHM/chm104 NJIT/CHM/chm203
touch NJIT/ECO/eco102
touch NJIT/PHY/phy102 NJIT/PHY/phy104
touch NJIT/PHY/PHYS/phys430

# recursively change permissions
# -rwx-r-x---
chmod -R 750 ~/NJIT
