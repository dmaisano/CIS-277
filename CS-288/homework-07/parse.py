from xml.dom.minidom import parse, parseString

file = "data.xhtml"

dom = parse("data.xhtml")

nodes = dom.getElementsByTagName("a")

for node in nodes:
    print(node.firstChild.nodeValue)

