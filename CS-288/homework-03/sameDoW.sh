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

# check if date1 is valid
if [ $(isValid $1) == 1 ]; then
	day1=$(date -d $(date -d $1 +'%Y-%m-%d') '+%A')
	echo "First day of the week is a $day1"
else
	echo "$1 - invalid date"
fi

# check if date2 is valid
if [ $(isValid $2) == 1 ]; then
	day2=$(date -d $(date -d $2 +'%Y-%m-%d') '+%A')
	echo "Second day of the week is a $day2"
else
	echo "$2 - invalid date"
fi

if [ $(isValid $1) == 1 ] && [ $(isValid $2) == 1 ]; then

	if [[ "$day1" == *$day2* ]]; then
		echo "Days of the week match."
	else
		echo "Days of the week don't match."
	fi

fi
