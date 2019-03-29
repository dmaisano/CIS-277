from socket import socket, AF_INET, SOCK_STREAM, SHUT_RDWR, SOL_SOCKET, SO_REUSEADDR
from datetime import datetime
from sys import argv
from os import path
from re import search


if len(argv) < 2:
    print("missing url")
    exit(1)

url = search("(http://)?(.+):([0-9]{4})(/.+)?", argv[1])

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

requestHeaders = "GET " + fileName + " HTTP/1.1\n"
requestHeaders += "Host: " + client.getsockname()[0] + ":" + client.getsockname()[1]
requestHeaders += "\n"

print(requestHeaders)
