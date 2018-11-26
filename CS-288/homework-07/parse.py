import sys
import re
import os
from xml.dom.minidom import parse

# returns the name of the file, regardless of the directory it resides in
def getFileName(path):
    fileName = path.split("/")
    fileName = fileName[len(fileName) - 1]

    return fileName.split(".")[0]


# returns the text from the given nodeList
def getText(nodeList):
    for node in nodeList.childNodes:
        if node.nodeType == node.TEXT_NODE:
            return str(node.nodeValue)


# returns a result string for a given table row
def getRowData(tr):
    res = []

    anchorText = ""
    exchange = "NASDAQ"
    symbol = ""
    company = ""
    volume = ""
    price = ""
    change = ""

    td = tr.getElementsByTagName("td")

    anchor = td[1].getElementsByTagName("a")[0]

    anchorText = getText(anchor)

    # match the company name and symbol
    matches = re.findall(r"[^\(\)]+", anchorText)

    symbol = matches[1].strip()

    company = matches[0].strip()

    volume = getText(td[2]).replace(",", "")

    price = getText(td[3]).replace(",", "").replace("$", "")

    change = getText(td[4])

    res = [exchange, symbol, company, volume, price, change]

    return ",".join(res)


# function to create the csv file
def createCSV(xhtmlFile):
    document = parse(xhtmlFile)

    # fetch the table containing the stock data
    table = document.getElementsByTagName("table")[2]

    # get all the table rows
    tableRows = table.getElementsByTagName("tr")

    # exclude the first row which contains the header
    tableRows = tableRows[1 : tableRows.length]

    # create the dir/filename
    outputFile = "data/" + getFileName(xhtmlFile) + ".csv"

    # create the csv file
    csvFile = open(outputFile, "w")

    header = "exchange,symbol,company,volume,price,change\n"
    csvFile.write(header)

    # write each row of data to the csv file
    for tr in tableRows:
        csvFile.write(getRowData(tr) + "\n")


# create directory if none exists
if not os.path.exists("./data"):
    os.makedirs("./data")

xhtmlFile = sys.argv[1]
createCSV(xhtmlFile)
