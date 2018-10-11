#!/bin/bash

# exit if no dir arg
if [ -z "$1" ]; then
	echo "No args"
	exit 1
fi

# array of counters "[0-9]"
# values initialized to zero
declare -a countArr=($(for i in {1..10}; do echo 0; done))

# create an array with all the files/dir inside ~/myDir
contents=($(ls $1))

# iterate through array using a counter
for file in "${contents[@]}"; do

	# slice and get the first char of the fileName
	# will be used as the index for the array
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
