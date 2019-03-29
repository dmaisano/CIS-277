from socket import socket, AF_INET, SOCK_STREAM, SHUT_RDWR, SOL_SOCKET, SO_REUSEADDR
from datetime import datetime, time
from sys import argv
from os import path
from re import match


def cacheFile(htmlString: str):
    print(htmlString)
    cachedFile = open("cache.html", "w")
    cachedFile.write(htmlString)
    cachedFile.close()


if len(argv) < 2:
    print("missing url")
    exit(1)

url = match(r"(http://)?(.+):([0-9]{4})(/.+)?", argv[1])

if not url.groups(4):
    print("missing filename")
    exit(1)

host = url.group(2)
port = int(url.group(3))
fileName = url.group(4)


# create TCP socket
client = socket(AF_INET, SOCK_STREAM)

# connect to remote host
client.connect((host, port))

# check if file is already cached
filePath = path.dirname(path.realpath(__file__)) + "/cache.html"
isCached = path.isfile(filePath)

# initialize request headers
requestHeaders = "GET " + fileName + " HTTP/1.1\r\n"
requestHeaders += "Host: " + host + ":" + str(port) + "\r\n"

if isCached:
    modifiedTime = path.getmtime(filePath)
    modifiedTime = datetime.utcfromtimestamp(modifiedTime)
    modifiedTime = modifiedTime.strftime("%a, %d %b %Y %H:%M:%S GMT\r\n")
    requestHeaders += "If-Modified-Since: " + modifiedTime
    requestHeaders += "\r\n"
else:
    requestHeaders += "\r\n"

client.send(requestHeaders.encode("utf-8"))


PACKET_SIZE = 10000
response = client.recv(PACKET_SIZE)
response: str = response.decode()

startIndex = response.find("Content-Type: text/html; charset=UTF-8\r\n\r\n")

if startIndex == -1:
    htmlFile = ""
else:
    htmlFile = response[startIndex + 40 : len(response)]

if isCached:
    isModified = response.find("HTTP/1.1 200 Ok")

    if htmlFile != "":
        print("file has been modified")
        cacheFile(htmlFile)
    else:
        print("file has not been modified")
else:
    cacheFile(htmlFile)

client.close()
