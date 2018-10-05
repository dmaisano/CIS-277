#!/bin/bash

# isValid() {
# 	echo 1
# }

# if [ $(isValid) ]; then
# 	echo "owo"
# fi

# returns true if valid, else 0
function isValid() {
	if [[ $1 =~ ($regex) ]] && date -d "$1" "+%Y-%m-%d" >/dev/null 2>&1; then
		echo 1
	else
		echo 2
	fi
}

# echo  $(dateMatch $1)

# if [ $(dateMatch $1) != 0 ]; then
# 	echo $1
# fi

function isDateInvalid() {
  # date -d "$1" "+%Y-%m-%d" > /dev/null 2>&1
  # res=$?
  # echo "$res"
	# date "+%Y-%m-%d" -d $1 > /dev/null  2>&1
 	# is_valid=$?
	# echo "$is_valid"

	# regex date pattern
	regex=^[0-9]{4}-[0-9]{2}-[0-9]{2}$

	if [[ $1 =~ ($regex) ]] && date -d "$1" "+%Y-%m-%d" >/dev/null 2>&1; then
		echo "owo"
	else
		echo "failed"
	fi
}

echo $(isDateInvalid $1)
