from socket import socket, AF_INET, SOCK_DGRAM, timeout
from time import sleep
from random import randint
import struct
import sys

ip = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 3000


# default bufferSize 4096 bytes
bufferSize = 4096

server = socket(AF_INET, SOCK_DGRAM)
server.bind((ip, port))
server.settimeout(0.5)

print("Server listening on %s:%d" % (ip, port))

while True:
    try:
        data, clientAddress = server.recvfrom(bufferSize)
    except timeout:
        continue
    # gracefully shut down the server
    except KeyboardInterrupt:
        server.close()
        exit(0)
    else:
        print("Receive data from client %s, %d: %s" % (*clientAddress, data.decode()))

        server.sendto(data, clientAddress)
        print("Sending data to   client %s, %d: %s\n" % (*clientAddress, data.decode()))

