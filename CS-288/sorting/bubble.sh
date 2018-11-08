#!/bin/bash
# Bubble Sort

echo "Enter Numbers to be Sorted : "
read -a arr

n=${#arr[@]}

# assume the array is already sorted
sorted=true

# run the sort
for ((i = 0; i < n; i++)); do

	# last i elements are already in place
	for ((j = i; j < n - i - 1; j++)); do

		if ((${arr[j]} > ${arr[$((j + 1))]})); then
			# swap
			temp=${arr[$j]}
			arr[$j]=${arr[$((j + 1))]}
			arr[$((j + 1))]=$temp

			sorted=false
		fi
	done

	# no swaps, O(N) time complexity
	if [ $i -eq $((n - 1)) ] && [ $sorted = true ]; then
		echo "array is already sorted"
	fi

done

printf "\nsorted array\n"
echo ${arr[*]}
