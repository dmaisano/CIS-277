import sys
import mysql.connector
from xml.dom.minidom import parse

username = sys.argv[2]
password = sys.argv[3]
xhtmlFile = sys.argv[1]

timestamp = xhtmlFile.split("/")
timestamp = timestamp[len(timestamp) - 1].split(".")[0]


# inserts a row of values into the table
def insert(cursor, values):
    query = "INSERT INTO nasdaq(timestamp,exchange,symbol,company,volume,price,percentChange) VALUES (%s,%s,%s,%s,%s,%s,%s)"
    cursor.execute(query, values)


# returns the text from the given nodeList
def getText(nodeList):
    for node in nodeList.childNodes:
        if node.nodeType == node.TEXT_NODE:
            return str(node.nodeValue)


# returns a tuple of values
def getRowData(tr):
    td = tr.getElementsByTagName("td")
    anchor = td[1].getElementsByTagName("a")[0]
    anchorText = getText(anchor).split("(")
    company = anchorText[0].strip()
    symbol = anchorText[1][: len(anchorText[1]) - 2]
    volume = getText(td[2]).replace(",", "")
    price = getText(td[3]).replace(",", "").replace("$", "")
    percentChange = getText(td[4])
    return (timestamp, "Nasdaq", symbol, company, volume, price, percentChange)


if len(sys.argv) < 3:
    print("missing args")
    exit(1)


try:
    cnx = mysql.connector.connect(
        host="localhost", user=username, password=password, database="demo"
    )
    cursor = cnx.cursor()

    document = parse(xhtmlFile)
    table = document.getElementsByTagName("table")[2]
    tableRows = table.getElementsByTagName("tr")[1:]

    for tr in tableRows:
        values = getRowData(tr)
        insert(cursor, values)

    # commit and close
    cnx.commit()
    cursor.close()
except mysql.connector.Error as err:
    print(err)
finally:
    try:
        cnx
    except NameError:
        pass
    else:
        cnx.close()
