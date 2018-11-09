#!/bin/bash
# Bubble Sort

function bubbleSort() {
	local -a arr=($@)
	local n=$(($# - 1))

	for ((i = 0; i < n; i++)); do
		# flag
		swapped=0

		for ((j = 0; j < n; j++)); do
			next=$((j + 1))

			if ((arr[j] > arr[next])); then
				local tmp=${arr[$j]}
				arr[$j]=${arr[$next]}
				arr[$next]=$tmp
				swapped=1
			fi
		done

		# if no elements were swapped after one pass
		# then array is already sorted, break
		if [ $swapped -eq 0 ]; then
			break
		fi

	done

	# return the sorted array
	echo ${arr[@]}
}

echo "Enter Numbers to be Sorted: "
read -a arr

printf "\nsorted array:\n$(bubbleSort ${arr[@]})\n"
