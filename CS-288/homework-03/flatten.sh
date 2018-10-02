#!/bin/bash

# cd to NJIT dir
cd ~/NJIT

# write output to listing file in $HOME dir
ls -lR > ~/listing

# move all files from subdirs to '~/NJIT' dir
find . -type f -exec mv -f {} ~/NJIT \;

# remove subdirectories
rm -R `ls -1 -d */`

# append new output of command
ls -lR >> ~/listing
