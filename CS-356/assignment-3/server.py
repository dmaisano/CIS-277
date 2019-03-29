from socket import socket, AF_INET, SOCK_STREAM, SHUT_RDWR, SOL_SOCKET, SO_REUSEADDR
from datetime import datetime
from typing import List
from sys import argv
from os import path
import re


ip = argv[1] if len(argv) >= 2 else "127.0.0.1"
port = int(argv[2]) if len(argv) >= 3 else 8080

# create TCP socket
server = socket(AF_INET, SOCK_STREAM)

# override socket if already in use
server.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

try:
    server.bind((ip, port))
    server.listen(1)
    print("Server listening on http://%s:%d" % (ip, port))
except Exception as e:
    print("Failed to bind server to %s:%d" % (ip, port))
    print(e)
    exit(1)

while True:
    try:
        conn, address = server.accept()

        PACKET_SIZE = 100000
        headers: List[str] = str(conn.recv(PACKET_SIZE).decode("utf-8")).splitlines()

        fileName = ""

        for header in headers:
            print(header)
            if re.match(r"GET .+ HTTP/1.1", header):
                fileName = re.match(r"GET (.+) HTTP/1.1", header).groups()[0]

        filePath: str = path.dirname(path.realpath(__file__)) + fileName

        header: bytes = b""
        response: bytes = b""

        date: str = datetime.utcnow().strftime("%a, %d %b %Y %H:%M:%S GMT")

        try:
            __path__ = path.dirname(path.realpath(__file__))
            response = open(filePath, "rb").read()

            modifiedTime = path.getmtime(filePath)
            modifiedTime = datetime.utcfromtimestamp(modifiedTime)
            modifiedTime = modifiedTime.strftime("%a, %d %b %Y %H:%M:%S GMT")

            header = "HTTP/1.1 200 OK\n"
            header += "Date: " + date + "\n"
            header += "Last-Modified: " + modifiedTime + "\n"
            header += "Content-Length: " + str(path.getsize(filePath)) + "\n"
            header += "Content-Type: text/html; charset=UTF-8\n"
            header += "\n"
        except Exception as e:
            # send 404 response / file not found
            header = "HTTP/1.1 404 Not Found\n"
            header += "Date: " + date + "\n\n"
            response = b""

        conn.send(header.encode("utf-8") + response)
        conn.close()

    except KeyboardInterrupt:
        server.close()
        break
