import sys
from socket import socket, AF_INET, SOCK_DGRAM

if len(sys.argv) < 2:
    print("missing IP and port")
    exit(1)

ip = sys.argv[1]
port = int(sys.argv[2])
max_data_len = 4096

server = socket(AF_INET, SOCK_DGRAM)
server.bind((ip, port))

print("server is running: http://%s:%s" % (ip, str(port)))

# listen for requests
while True:
    request = server.recv(max_data_len)
    print(request)
