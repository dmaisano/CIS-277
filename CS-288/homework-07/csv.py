import sys
import os
from xml.dom.minidom import parse

directory = "csv-data"

# returns extensionless filename
def getFileName(path):
    fileName = path.split("/")
    return fileName[len(fileName) - 1].split(".")[0]


# returns the text from the given nodeList
def getText(nodeList):
    for node in nodeList.childNodes:
        if node.nodeType == node.TEXT_NODE:
            return str(node.nodeValue)


# returns a result string for a given table row
def getRowData(tr):
    td = tr.getElementsByTagName("td")
    anchor = td[1].getElementsByTagName("a")[0]
    anchorText = getText(anchor).split("(")
    company = anchorText[0].strip()
    symbol = anchorText[1][: len(anchorText[1]) - 2]
    volume = getText(td[2]).replace(",", "")
    price = getText(td[3]).replace(",", "").replace("$", "")
    change = getText(td[4])
    return ",".join(["Nasdaq", symbol, company, volume, price, change])


def createCSV(xhtmlFile):
    document = parse(xhtmlFile)
    # fetch the table containing the stock data
    table = document.getElementsByTagName("table")[2]
    # exclude the first row which contains the header
    tableRows = table.getElementsByTagName("tr")[1:]
    # create the dir/filename
    outputFile = "%s/%s.csv" % (directory, getFileName(xhtmlFile))
    csvFile = open(outputFile, "w")
    header = "exchange,symbol,company,volume,price,change\n"
    csvFile.write(header)
    # write each row of data to the csv file
    for tr in tableRows:
        csvFile.write(getRowData(tr) + "\n")


# create directory if none exists
if not os.path.exists(directory):
    os.makedirs(directory)

createCSV(sys.argv[1])
