#!/bin/bash

# run
# drop database for testing purposes only

mysql -u $USER -p <nasdaq.sql

# tag soup url
# "http://vrici.lojban.org/\~cowan/XML/tagsoup/tagsoup-1.2.1.jar"

# nasdaqUrl="http://wsj.com/mdc/public/page/2_3021-activnnm-actives.html"

# convertHTML() {
# 	# download snapshot of the most active stocks
# 	curl --output "html/$timestamp.html" --url $nasdaqUrl

# 	# convert html to xhtml
# 	java -jar tagsoup-1.2.1.jar "html/$timestamp.html" >"xhtml/$timestamp.xhtml"
# }

# mkdir -p ./html ./xhtml

# minutes=60
# for ((i = 0; i < $minutes; i++)); do
# 	timestamp="$(date +"%Y-%m-%d-%H-%M-%S")"
# 	convertHTML $nasdaqUrl
# 	# python3 nasdaq.py "xhtml/$timestamp.xhtml"
# 	sleep 60
# done
