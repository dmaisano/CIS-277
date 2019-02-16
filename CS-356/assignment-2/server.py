from socket import socket, AF_INET, SOCK_DGRAM, timeout
from random import randint, uniform
from time import sleep
import struct
import sys

ip = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 3000

# default bufferSize 4096 bytes
bufferSize = 4096

server = socket(AF_INET, SOCK_DGRAM)
server.bind((ip, port))
server.settimeout(1)

print("Server listening on %s:%d" % (ip, port))


while True:
    try:
        data, clientAddress = server.recvfrom(bufferSize)
        sequence = struct.unpack("!ii", data)[1]

        if randint(0, 10) < 4:
            print("Message was dropped, sequence=%d" % (sequence))
        else:
            reply = struct.pack("!ii", 2, sequence)

            sleep(uniform(0.1, 0.9))

            server.sendto(reply, clientAddress)
    except timeout:
        continue

    # gracefully shut down the server
    except KeyboardInterrupt:
        server.close()
        exit(0)
