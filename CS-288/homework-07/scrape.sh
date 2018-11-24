#!/bin/bash

# download tagsoup if not exist
if [ ! -f "./tagsoup-1.2.1.jar" ]; then
	curl "http://vrici.lojban.org/\~cowan/XML/tagsoup/tagsoup-1.2.1.jar"
fi

url="http://wsj.com/mdc/public/page/2_3021-activnnm-actives.html"

scrape() {
	local url=$1
	local timestamp="$(date +"%Y-%m-%d-%H-%M-%S")"

	# create data folder if not exist
	mkdir -p ./data

	# get a snapshot of the most active stocks
	wget $url -O "data/$timestamp.html"

	# convert cr*p html to xhtml
	java -jar tagsoup-1.2.1.jar --files "data/$timestamp.html"

	# remove old file
	rm -rf "data/$timestamp.html"
}

for ((i = 0; i < 60; i++)); do
	scrape $url
	sleep 60
done
