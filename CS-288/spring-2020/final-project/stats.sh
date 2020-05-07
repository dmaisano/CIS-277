#!/bin/bash

if [ -z "$1" ]; then
	echo "Missing url param"
	exit 1
fi

printf "Enter MySQL username: "
read username

printf "Enter MySQL password: "
read -s password

# run the SQL script
mysql --user=$username --password=$password < "create_tables.sql"

while :
do
	# scrape latest covid19 data
	curl -s --output "covid_stats.html" --url $1

	# convert to xhtml
	java -jar tagsoup-1.2.1.jar "covid_stats.html" > "covid_stats.xhtml"

	python3 parser.py "covid_stats.xhtml" $username $password

	# clean up files
	# rm "*.html" "*.xhtml"

	# wait 30 min before refreshing data
	echo "will refresh data in 30min"
	sleep 1800
done
