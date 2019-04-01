from socket import socket, AF_INET, SOCK_STREAM, SHUT_RDWR, SOL_SOCKET, SO_REUSEADDR
from datetime import datetime, time
from typing import List
from sys import argv
from os import path
from re import match


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
        cacheModifiedTime = False

        for header in headers:
            if match(r"GET .+ HTTP/1.1", header):
                fileName = match(r"GET (.+) HTTP/1.1", header).groups()[0]

            if match(r"If-Modified-Since: (.+)", header):
                cacheModifiedTime = match(
                    r"If-Modified-Since: (.+) GMT", header
                ).groups()[0]
                cacheModifiedTime = datetime.strptime(
                    cacheModifiedTime, "%a, %d %b %Y %H:%M:%S"
                )

        filePath: str = path.dirname(path.realpath(__file__)) + fileName

        responseHeaders: str = ""
        responseBody = b""

        date: str = datetime.utcnow().strftime("%a, %d %b %Y %H:%M:%S GMT\r\n")

        try:
            responseBody = open(filePath, "rb").read()

            # get time file was last modified
            lastModified = path.getmtime(filePath)
            lastModified = datetime.utcfromtimestamp(lastModified).replace(
                microsecond=0
            )

            # HTTP 200 Response
            responseHeaders = "HTTP/1.1 200 OK\r\n"
            responseHeaders += "Date: " + date
            responseHeaders += "Last-Modified: " + lastModified.strftime(
                "%a, %d %b %Y %H:%M:%S GMT\r\n"
            )
            responseHeaders += "Content-Length: " + str(path.getsize(filePath)) + "\r\n"
            responseHeaders += "Content-Type: text/html; charset=UTF-8\r\n"
            responseHeaders += "\r\n"

            if cacheModifiedTime:
                if lastModified <= cacheModifiedTime:
                    responseHeaders = "HTTP/1.1 304 Not Modified\r\n"
                    responseHeaders += "Date: " + date
                    responseHeaders += "\r\n"
                    responseBody = b""

        except:
            # send 404 response / file not found
            responseHeaders: str = "HTTP/1.1 404 Not Found\r\n"
            responseHeaders += "Date: " + date
            responseHeaders += "\r\n"
            responseBody: bytes = b""

        conn.send(responseHeaders.encode("utf-8") + responseBody)
        conn.close()

    except KeyboardInterrupt:
        server.close()
        break
