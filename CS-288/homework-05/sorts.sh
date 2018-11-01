#!/bin/bash

# bash script to automatically run the sorting alogrithms

function runSorts() {
	./merge.exe $1
	./radix.exe $1
	# ./selection.exe $1

	# append new line
	echo '' >>results.txt
}

# compile the files
gcc -ansi merge.c -g -o merge.exe
gcc -ansi radix.c -g -o radix.exe
gcc -ansi selection.c -g -o selection.exe

# clear the file

>results.txt

# run the sorting alogorithms
# runSorts 10
# runSorts 100
# runSorts 1000
# runSorts 10000
# runSorts 100000
# runSorts 500000
