#!/bin/bash

# download tagsoup if needed
if [ ! -f "./tagsoup-1.2.1.jar" ]; then
	curl --output tagsoup-1.2.1.jar --url "http://vrici.lojban.org/\~cowan/XML/tagsoup/tagsoup-1.2.1.jar"
fi

scrape() {
	local url="http://wsj.com/mdc/public/page/2_3021-activnnm-actives.html"
	local timestamp="$(date +"%Y-%m-%d-%H-%M-%S")"

	# download snapshot of the most active stocks
	curl --output "raw/$timestamp.html" --url $url

	# convert downloaded html to xhtml
	java -jar tagsoup-1.2.1.jar --files "raw/$timestamp.html"

	# remove old file
	rm -rf "raw/$timestamp.html"
}

# create directory if none exists
mkdir -p ./raw

# download the stocks every min for 1hr
for ((i = 0; i < 60; i++)); do
	scrape $url
	sleep 60
done
