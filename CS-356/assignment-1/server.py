import sys
from socket import socket, AF_INET, SOCK_DGRAM

ip = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 8080

# default buffer size 4096 bytes
bufferSize = 4096

server = socket(AF_INET, SOCK_DGRAM)
server.bind((ip, port))

print("server is running %s:%d" % (ip, port))

# listen for requests
while True:
    data, clientAddress = server.recvfrom(bufferSize)

    print("Receive data from client %s, %d: %s" % (*clientAddress, data.decode()))

    # echo back to the client
    server.sendto(data, clientAddress)

    print("Sending data to   client %s, %d: %s" % (*clientAddress, data.decode()))
