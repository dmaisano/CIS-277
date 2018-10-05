#!/bin/bash

# exit if no dir arg
if [ -z "$1" ]; then echo "No args"; fi

# array of counters "[0-9]"
declare -a countArr=($(for i in {1..10}; do echo 0; done))

# create an array with all the files/dir inside ~/myDir
contents=($(ls $1))

# iterate through array using a counter
for file in "${contents[@]}"; do

	# store the index
	index="${file:0:1}"

	# files that start with a number "[0-9]"
	if [[ $index =~ ^([0-9])$ ]]; then

		# increment the occurence
		((countArr["$index"]++))
	fi

done

for i in "${!countArr[@]}"; do
	echo $i ${countArr[i]}
done
