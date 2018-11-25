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

    symbol = anchorText[anchorText.find("(") + 1 : anchorText.find(")")]

    company = re.search(r"[^\(\)\n]+", anchorText)[0]

    print("symbol: %s\ncompany: %s" % (symbol, company))
    print(anchorText)
