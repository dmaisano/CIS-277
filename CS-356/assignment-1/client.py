import sys
from socket import socket, AF_INET, SOCK_DGRAM

if len(sys.argv) < 3:
    print("missing args")
    exit(1)

host = sys.argv[1]
port = int(sys.argv[2])
count = int(sys.argv[3])

# data to be sent
payload = "X" * count

client = socket(AF_INET, SOCK_DGRAM)

print("sending payload to %s:%s\npayload: %s" % (host, port, payload))

# send the data
client.sendto(payload.encode(), (host, port))

# setting large default buffer size
bufferSize = 4096

# receive a response
response = client.recv(bufferSize)
