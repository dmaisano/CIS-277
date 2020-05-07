import mysql.connector
from sys import argv, exc_info
from xml.dom.minidom import parse, Element, NodeList, Node
from os import path, remove


# inserts a row of values into the table
def insertRow(cursor, values):
    query = """
        INSERT INTO covid_cases (us_state,confirmed_cases,new_cases,confirmed_deaths,new_deaths) VALUES (%s,%s,%s,%s,%s)
        ON DUPLICATE KEY UPDATE confirmed_cases=%s,new_cases=%s,confirmed_deaths=%s,new_deaths=%s
        """

    cursor.execute(query, [*values, *values[1:]])


def getRowData(tr: Node):
    stateName = ""

    stateNode = tr.childNodes[0]
    if stateNode.childNodes.length == 1:
        stateName = stateNode.firstChild.nodeValue

    # state name is contained within an anchor tag
    else:
        anchor = stateNode.getElementsByTagName("a")[0]
        stateName = anchor.firstChild.nodeValue

    values = [stateName.strip()]

    for td in tr.childNodes[1:5]:
        tmp = str(td.firstChild.nodeValue).strip().replace(",", "")
        tmp = 0 if tmp == "" else int(tmp)
        values.append(tmp)

    return values


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

    usaTotalStats = tableRows[1]

    # initialize mysql connection
    cnx = mysql.connector.connect(
        host="localhost", user=argv[2], password=argv[3], database="cs_288_covid"
    )
    cursor = cnx.cursor()
    for tr in tableRows[1:]:
        values = getRowData(tr)
        insertRow(cursor, values)

    cnx.commit()
    cnx.close()
except Exception as e:
    print(e)
finally:
    try:
        fileName = argv[1].split(".")[0]

        remove(argv[1])
        remove(fileName + ".html")

        cnx
    except NameError:
        pass
    else:
        cnx.close()
