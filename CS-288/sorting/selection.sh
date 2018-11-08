#!/bin/bash
# Selection Sort

selectionSort() {
	for ((i = 0; i < n; i++)); do
		min=$i
		for ((j = i + 1; j < n; j++)); do
			if [ ${arr[j]} -lt ${arr[min]} ]; then
				min=$j
			fi
		done

		temp=${arr[$i]}

		arr[$i]=${arr[$min]}

		arr[$min]=$temp
	done
}

echo "Enter Numbers to be Sorted : "

read -a arr

n=${#arr[@]}

selectionSort

printf "\nsorted array\n"
echo ${arr[*]}
