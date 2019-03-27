from socket import socket, AF_INET, SOCK_STREAM
from os import path
from datetime import datetime
import sys


ip = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 8080

# create TCP socket
server = socket(AF_INET, SOCK_STREAM)

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
        # get the connection from the client
        connection, address = server.accept()

        PACKET_SIZE = 100000
        data: str = connection.recv(PACKET_SIZE).decode("utf-8")

        request: str = data.splitlines()[0]
        requestMethod: str = request.split()[0]
        fileName: str = request.split()[1]

        header: bytes = b""
        response: bytes = b""

        try:
            __path__ = path.dirname(path.realpath(__file__))
            response = open(__path__ + fileName, "rb").read()

            date = datetime.now().strftime("%a, %d %b %Y %H:%M:%S GMT")

            timestamp = path.getmtime(__path__ + fileName)
            lastModified = datetime.utcfromtimestamp(timestamp).strftime(
                "%a, %d %b %Y %H:%M:%S GMT"
            )
            lastModified = "Last-Modified: " + lastModified

            header = "HTTP/1.1 200 OK\nContent-Type: text/html\n%s\n\n" % (lastModified)
        except:
            # send 404 response
            header = "HTTP/1.1 404 Not Found\n"
            response = b""

        connection.send(header.encode("utf-8") + response)
        connection.close()

    except KeyboardInterrupt:
        server.close()
        break
