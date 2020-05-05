import mysql.connector
from sys import argv
from xml.dom.minidom import parse, Element, NodeList, Node

# inserts a row of values into the table
def insert(cursor, values):
    query = "INSERT INTO nasdaq (timestamp,exchange,symbol,company,volume,price,percentChange) VALUES (%s,%s,%s,%s,%s,%s,%s)"
    cursor.execute(query, values)


def main():
    try:
        xhtmlFile = argv[1]
        document = parse(xhtmlFile)

        dataTable: Element = None
        tables = document.getElementsByTagName("table")

        table: Element
        for table in tables:
            if table.getAttribute("id") == "usa_table_countries_today":
                dataTable = table
                break

        if dataTable == None:
            raise Exception("Invalid document, missing covid data")

        tableBody: Element = dataTable.childNodes[1]
        tableRows: NodeList = tableBody.childNodes

        print(tableBody.childNodes)
    except:
        print("Error")


main()
