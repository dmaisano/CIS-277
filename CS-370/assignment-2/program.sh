#!/bin/bash

# must be in same dir to run script

if [ -z "$1" ]; then
  echo "Missing Input File"
  exit -1
fi

javac DavisPutnam.java && java DavisPutnam $1