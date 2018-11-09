#!/bin/bash
# Selection Sort

selectionSort() {

	local -a arr=($@)
	local n=$#

	for ((i = 0; i < n - 1; i++)); do

		# find the min element in the unsorted array
		min=$i
		for ((j = i + 1; j < n; j++)); do
			if [ ${arr[j]} -lt ${arr[min]} ]; then
				min=$j
			fi
		done

		# swap the min element with the first element
		temp=${arr[$i]}
		arr[$i]=${arr[$min]}
		arr[$min]=$temp
	done

	# return the sorted array
	echo ${arr[@]}
}

echo "Enter Numbers to be Sorted: "
read -a arr

printf "sorted array:\n$(selectionSort ${arr[@]})\n"
