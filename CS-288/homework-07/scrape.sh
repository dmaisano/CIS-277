#!/bin/bash

# good url to scrape: "https://www.bloomberg.com/markets/stocks/world-indexes/americas"

if [ $# -lt 1 ]; then
	echo "missing url argument"
	exit 1
elif [ $# -gt 1 ]; then
	echo "too many args"
	exit 1
fi

url=$1
htmlFIle="data.html"
xmlFile="data.xml"

# download the raw html
wget -O $htmlFIle $url

# convert to xhtml
java -jar tagsoup.jar --files $htmlFIle

# remove old file
rm -rf $htmlFIle
