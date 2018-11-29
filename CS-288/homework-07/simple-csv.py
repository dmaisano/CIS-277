import sys
import xml.dom.minidom

title = sys.argv[1]
xhtml = xml.dom.minidom.parse(sys.argv[1])
table = xhtml.getElementsByTagName("table")[2]

# filename.csv
fileName = title.split(".")[0] + ".csv"

csvFile = open("foo.csv", "w")
csvFile.write("exchange,symbol,comapny,volume,price,change\n")

for tr in table.getElementsByTagName("tr")[1:]:
    data = ["Nasdaq"]

    i = 0
    for td in tr.getElementsByTagName("td"):

        if i == 0:
            i += 1
            continue

        if i == 1:
            anchor = td.getElementsByTagName("a")[0]
            anchorText = anchor.firstChild.nodeValue.split("(")
            symbol = anchorText[1].replace(")", "").replace("\n", "")
            company = anchorText[0].strip()

            data.append(symbol)
            data.append(company)

        else:
            nodeText = td.firstChild.nodeValue

            if nodeText == "\n":
                continue

            nodeText = nodeText.replace(",", "").replace("$", "")

            data.append(nodeText)

        i += 1

    data = data[: len(data) - 1]

    csvFile.write(",".join(data) + "\n")
