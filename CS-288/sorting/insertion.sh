#!/bin/bash
# Insertion Sort

insertionSort() {
	for ((i = 1; i < n; i++)); do

		tmp=${arr[i]}
		j=$((i - 1))

		while (($tmp < ${arr[j]})); do

			arr[$(($j + 1))]=${arr[j]}

			# decrement j
			let j--

			# check if j is out of bounds
			if [ $j -eq -1 ]; then
				break
			fi
		done

		arr[$((j + 1))]=$tmp
	done
}

echo "Enter Numbers to be Sorted : "

read -a arr

n=${#arr[@]}

insertionSort

printf "\nsorted arr\n"
echo ${arr[*]}
