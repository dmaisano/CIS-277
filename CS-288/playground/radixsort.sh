#!/bin/sh

function concatBuckets() {
	echo ${digit0Bucket[@]}
	echo ${digit1Bucket[@]}
	echo ${digit2Bucket[@]}
	echo ${digit3Bucket[@]}
	echo ${digit4Bucket[@]}
	echo ${digit5Bucket[@]}
	echo ${digit6Bucket[@]}
	echo ${digit7Bucket[@]}
	echo ${digit8Bucket[@]}
	echo ${digit9Bucket[@]}
}

function resetBuckets() {
	digit0Bucket=()
	digit1Bucket=()
	digit2Bucket=()
	digit3Bucket=()
	digit4Bucket=()
	digit5Bucket=()
	digit6Bucket=()
	digit7Bucket=()
	digit8Bucket=()
	digit9Bucket=()
}

n=0
for i in $@; do
	if [ $n -lt ${#i} ]; then
		n=${#i}
	fi
done
list=($(printf "%0${n}d " $@))

for ((m = n - 1; 0 <= m; --m)); do
	resetBuckets
	for i in ${list[@]}; do
		digit=${i:$m:1}
		case $digit in
		0) digit0Bucket+=($i) ;;
		1) digit1Bucket+=($i) ;;
		2) digit2Bucket+=($i) ;;
		3) digit3Bucket+=($i) ;;
		4) digit4Bucket+=($i) ;;
		5) digit5Bucket+=($i) ;;
		6) digit6Bucket+=($i) ;;
		7) digit7Bucket+=($i) ;;
		8) digit8Bucket+=($i) ;;
		9) digit9Bucket+=($i) ;;
		esac
	done
	list=($(concatBuckets))
done
echo ${list[@]}
