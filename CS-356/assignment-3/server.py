from socket import socket, AF_INET, SOCK_STREAM, SHUT_RDWR, SOL_SOCKET, SO_REUSEADDR
from os import path
from datetime import datetime
import sys


ip = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 8080

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
        data: str = conn.recv(PACKET_SIZE).decode("utf-8")

        request: str = data.splitlines()[0]
        requestMethod: str = request.split()[0]
        fileName: str = request.split()[1]

        header: bytes = b""
        response: bytes = b""

        date = datetime.utcnow().strftime("%a, %d %b %Y %H:%M:%S GMT")

        try:
            __path__ = path.dirname(path.realpath(__file__))
            response = open(__path__ + fileName, "rb").read()

            timestamp = path.getmtime(__path__ + fileName)
            lastModified = datetime.utcfromtimestamp(timestamp)
            lastModified = lastModified.strftime("%a, %d %b %Y %H:%M:%S GMT")

            header = "HTTP/1.1 200 OK\n"
            header += "Date: " + date + "\n"
            header += "Last-Modified: " + lastModified + "\n"
            header += "Content-Length: " + str(path.getsize(__path__ + fileName)) + "\n"
            header += "Content-Type: text/html; charset=UTF-8\n"
            header += "\n"
        except:
            # send 404 response / file not found
            header = "HTTP/1.1 404 Not Found\n"
            header += "Date: " + date + "\n\n"
            response = b""

        conn.send(header.encode("utf-8") + response)
        conn.close()

    except KeyboardInterrupt:
        server.close()
        break
