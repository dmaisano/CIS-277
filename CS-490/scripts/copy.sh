#!/bin/bash

# copy the contents of the project to the private repo

rm -rf ../njit/CS-490

rsync -a ./ ../njit/CS-490

cd ../njit/CS-490

echo "✅ successfully copied current project to $PWD"
