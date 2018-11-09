#!/bin/bash
# Insertion Sort

function insertionSort() {
	local -a arr=($@)
	local n=$#

	for ((i = 0; i < n; i++)); do
		local key=${arr[i]}
		local j=$((i - 1))

		# shift the elements greater than the key one position ahead
		while ((${arr[j]} > $key && $j >= 0)); do
			arr[$((j + 1))]=${arr[j]}

			# decrement j
			let j--
		done

		arr[$((j + 1))]=$key
	done

	# return the sorted array
	echo ${arr[@]}
}

echo "Enter Numbers to be Sorted: "
read -a arr

printf "\nsorted array:\n$(insertionSort ${arr[@]})\n"
