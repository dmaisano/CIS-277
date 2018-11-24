import sys
from xml.dom.minidom import parse

xhtmlFile = sys.argv[1]
document = parse(xhtmlFile)

# fetch the table
table = document.getElementsByTagName("table")[2]

# data to be stored in csvFile
data = ["exchange,symbol,company,volume,price,change"]

# helper function to return text from an element
def getText(element):
    for node in element:
        if node.nodeType == node.TEXT_NODE:
            print(node.nodeValue)


for tr in table.getElementsByTagName("tr"):
    res = []

    anchor = tr.getElementsByTagName("a")

    print(anchor.firstChild.nodeValue)

    # print(getText(anchor))

    # for td in tr.getElementsByTagName("td"):

    # for node in td.childNodes:
    #     if node.nodeType == node.TEXT_NODE:
    #         print(node.nodeValue)

