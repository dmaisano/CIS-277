#!/bin/bash

if [[ -z "$1" ]]; then
	echo "Missing url param"
	exit 1
fi

# printf "Enter MySQL username: "
# read username

# printf "Enter MySQL password: "
# read -s password

# # run the SQL script
# mysql --user=$username --password=$password < covid_tracker.sql

# ensure directories exist
mkdir -p html
mkdir -p xhtml

while :
do
	timestamp="$(date +"%Y-%m-%d-%H-%M-%S")"

	# scrape latest covid19 data
	curl -s --output "html/$timestamp.html" --url $1

	# convert to xhtml
	java -jar tagsoup-1.2.1.jar "html/$timestamp.html" > "xhtml/$timestamp.xhtml"

	# remove the html file(s) as it is no longer needed
	# rm -r html/*

	# python3 covid_sql.py "xhtml/$timestamp.xhtml" $username $password

	# wait 30 min before refreshing data
	echo "will refresh data in 30min"
	sleep 1800
done
