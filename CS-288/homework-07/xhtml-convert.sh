#!/bin/bash

# tag soup url
# "http://vrici.lojban.org/\~cowan/XML/tagsoup/tagsoup-1.2.1.jar"

convertHTML() {
	url="http://wsj.com/mdc/public/page/2_3021-activnnm-actives.html"
	timestamp="$(date +"%Y-%m-%d-%H-%M-%S")"

	# download snapshot of the most active stocks
	curl --output "xhtml/$timestamp.html" --url $url

	# convert html to xhtml
	java -jar tagsoup-1.2.1.jar --files "xhtml/$timestamp.html"

	# remove old file
	rm -rf "xhtml/$timestamp.html"
}

mkdir -p ./xhtml

# download the stocks every min for 1hr
for ((i = 0; i < 60; i++)); do
	convertHTML $url
	sleep 60
done
