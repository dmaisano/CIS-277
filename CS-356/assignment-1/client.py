import sys
from socket import socket, AF_INET, SOCK_DGRAM, error

host = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 8080
count = int(sys.argv[3]) if len(sys.argv) >= 4 else 10

# default buffer size 4096 bytes
bufferSize = 4096

# data to be sent
payload = "X" * count

client = socket(AF_INET, SOCK_DGRAM)
client.settimeout(1)

print("Sending data to   %s, %d: %s" % (host, port, payload))

# send the data
client.sendto(payload.encode(), (host, port))

# receive a response
response, serverAddress = client.recvfrom(bufferSize)

print("Receive data from %s, %d: %s" % (*serverAddress, response.decode()))
