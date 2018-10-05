#!/bin/bash

# exit if missing 2 dates
if (("$#" < 2)); then
	echo "No args"
	exit 1
fi

# returns true if valid, else 0
function isValid() {
	# regex pattern for valid date
	regex=^[0-9]{4}-[0-9]{2}-[0-9]{2}$

	if [[ $1 =~ ($regex) ]] && date -d "$1" "+%Y-%m-%d" >/dev/null 2>&1; then
		echo 1
	else
		echo 0
	fi
}

# returns day of week or err msg
function getDow() {
	# check if date is valid
	if [ $(isValid $1) == 1 ]; then
		day=$(date -d $(date -d $1 +'%Y-%m-%d') '+%A')
		echo "$2 day of the week is a $day"
	else
		echo "$1 - invalid date"
	fi
}

function printDow() {
	# check if date is valid
	if [ $(isValid $1) == 1 ]; then
		day=$(date -d $(date -d $1 +'%Y-%m-%d') '+%A')
		echo "$2 day of the week is a $day"
	elif [ $(isValid $1) == 1 ] && [ $2 == "getDow" ]; then
		day=$(date -d $(date -d $1 +'%Y-%m-%d') '+%A')
		echo "$day"
	else
		echo "$1 - invalid date"
	fi
}

# run the functions
echo $(getDow $1 "First")
echo $(getDow $2 "Second")

if [ $(isValid $1) == 1 ] && [ $(isValid $2) == 1 ]; then

	if [[ "$(getDow $1 "getDow")" == *$(getDow $2 "getDow")* ]]; then
		echo "Days of the week match."
	else
		echo "Days of the week don't match."
	fi

fi

# $(isValid $arg) checks if date is given in a valid format
if [ $(isValid $1) == 1 ] && [ $(isValid $2) == 1 ]; then

	if [[ "$day1" == *$day2* ]]; then
		echo "Days of the week match."
	else
		echo "Days of the week don't match."
	fi

fi
