#!/bin/bash

# tag soup url
# "http://vrici.lojban.org/\~cowan/XML/tagsoup/tagsoup-1.2.1.jar"

url="http://wsj.com/mdc/public/page/2_3021-activnnm-actives.html"

convertHTML() {
	# download snapshot of the most active stocks
	curl --output "html/$timestamp.html" --url $url

	# convert html to xhtml
	java -jar tagsoup-1.2.1.jar "html/$timestamp.html" >"xhtml/$timestamp.xhtml"
}

mkdir -p ./html ./xhtml ./csv-data

# download the stocks every min for 1hr
for ((i = 0; i < 60; i++)); do
	timestamp="$(date +"%Y-%m-%d-%H-%M-%S")"
	convertHTML $url
	python3 csv.py "xhtml/$timestamp.xhtml"
	sleep 60
done
