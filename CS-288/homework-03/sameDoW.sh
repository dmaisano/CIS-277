#!/bin/bash
set -e

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
		# return the date
		echo "$(date -d $(date -d $1 +'%Y-%m-%d') '+%A')"
	else
		echo 1
	fi
}

# exit if any date is invalid
for arg in "$@"; do
	if [ $(getDow $arg) == 1 ]; then
		echo "$arg ~ invalid date"
		exit 1
	fi
done

day1=$(getDow $1)
day2=$(getDow $2)

echo "First day of the week is a $day1"
echo "Second day of the week is a $day2"

if [[ "$day1" == "$day2" ]]; then
	echo "Days of the week match."
else
	echo "Days of the week don't match."
fi
