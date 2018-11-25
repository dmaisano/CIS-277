import sys
import re
from xml.dom.minidom import parse

xhtmlFile = sys.argv[1]
document = parse(xhtmlFile)

# fetch the table
table = document.getElementsByTagName("table")[2]

# data to be stored in csvFile
data = ["exchange,symbol,company,volume,price,change"]

# helper function to return text from an element
def getText(arg):
    for element in arg:
        for node in element.childNodes:
            if node.nodeType == node.TEXT_NODE:
                return node.nodeValue


for tr in table.getElementsByTagName("tr"):
    res = []

    anchorText = ""
    exchange = "NASDAQ"
    symbol = ""
    company = ""
    volume = ""
    price = ""
    change = ""

    td = tr.getElementsByTagName("td")

    anchor = td[1].getElementsByTagName("a")

    anchorText = str(getText(anchor))

    matches = re.findall(r"[^\(\)\n]+", anchorText)

    company = str(matches[0]).strip()

    symbol = str(matches.pop()).strip()

    print(symbol)
    print(company)
    print(anchorText)
