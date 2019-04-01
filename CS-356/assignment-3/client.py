from socket import socket, AF_INET, SOCK_STREAM, SHUT_RDWR, SOL_SOCKET, SO_REUSEADDR
from datetime import datetime, time
from sys import argv
from os import path
from re import match


def cacheFile(htmlString: str):
    cachedFile = open("cache.html", "w")
    cachedFile.write(htmlString)
    cachedFile.close()


if len(argv) < 2:
    print("missing url")
    exit(1)

url = match(r"(http://)?(.+):([0-9]{4})(/.+)?", argv[1])

if not url.group(4):
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

print(requestHeaders)

client.send(requestHeaders.encode("utf-8"))


PACKET_SIZE = 10000
response = client.recv(PACKET_SIZE)
response: str = response.decode()

startIndex = response.find("Content-Type: text/html; charset=UTF-8\r\n\r\n")


if startIndex == -1:
    htmlFile = ""
else:
    htmlFile = response[startIndex + 42 : len(response)]

is200 = response.find("HTTP/1.1 200 OK")
is304 = response.find("HTTP/1.1 304 Not Modified")
is404 = response.find("HTTP/1.1 404 Not Found")


if is404 != -1:
    print(response)

if is200 != -1 and not isCached:
    print(response)
    cacheFile(htmlFile)

if is200 != -1 and isCached:
    print("file has been modified\n")
    print(response)
    cacheFile(htmlFile)

if is304 != -1:
    print("file has not been modified")
    print(response)

client.close()
