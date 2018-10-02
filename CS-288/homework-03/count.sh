#!/bin/bash

# exit if no dir arg
if [ -z "$1" ]; then echo "No args"; fi

# 0-9 digits
countArr=(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

# count function
count() {

	# create an array with all the filer/dir inside ~/myDir
	contents=("$1"/*)

	# iterate through array using a counter
	for file in "${contents[@]}"; do
		echo "$file"
	done


	# "$1": dir argument
}

count $1
