# from xml.dom.minidom import parse
import xml.dom.minidom as dom

file = "data.xhtml"

dom = dom.parse("data.xhtml")

nodes = dom.getElementsByTagName("div")

for node in nodes:
    print(node.firstChild)
    print(node.firstChild.nodeValue)
    if node.hasAttribute("buyer-title"):
        print(node.firstChild.nodeValue)
