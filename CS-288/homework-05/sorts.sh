#!/bin/bash

# bash script to automatically run the sorting alogrithms

function runSorts() {
	./merge $1
	./radix $1
	./selection $1

	# append new line
	echo '' >>results.txt
}

# compile the files
gcc -ansi -w merge.c -o merge
gcc -ansi -w radix.c -o radix
gcc -ansi -w selection.c -o selection

# clear the file

>results.txt

# run the sorting alogorithms
runSorts 10
runSorts 100
runSorts 1000
runSorts 10000
runSorts 100000
runSorts 1000000
