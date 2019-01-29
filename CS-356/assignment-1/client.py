import sys
from socket import socket, AF_INET, SOCK_DGRAM, timeout

host = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 3000
count = int(sys.argv[3]) if len(sys.argv) >= 4 else 10

# default bufferSize 4096 bytes
bufferSize = 4096

# data to be sent
payload = "X" * count

client = socket(AF_INET, SOCK_DGRAM)
client.settimeout(1)

numRetries = 0
while numRetries < 3:
    try:
        client.sendto(payload.encode(), (host, port))
        print("Sending data to   %s, %d: %s" % (host, port, payload))

        client.settimeout(1)
        data, serverAddress = client.recvfrom(bufferSize)
    except timeout:
        print("Message timed out")
        numRetries += 1
    except KeyboardInterrupt:
        client.close()
        exit(0)
    else:
        print("Receive data from %s, %d: %s" % (*serverAddress, data.decode()))
        break
