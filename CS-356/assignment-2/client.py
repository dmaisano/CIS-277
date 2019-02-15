from socket import socket, AF_INET, SOCK_DGRAM, timeout
from time import time
import struct
import sys

host = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 3000

# default bufferSize 4096 bytes
bufferSize = 4096

# map of round trip times
tripTimes = {}

client = socket(AF_INET, SOCK_DGRAM)
client.settimeout(1)

print("Connecting to %s:%d" % (host, port))

for i in range(10):
    try:
        # get the current start time
        startTime = time()

        # pack the data using network big endian
        data = struct.pack("!ii", 1, i)

        client.sendto(data, (host, port))

        response, serverAddress = client.recvfrom(bufferSize)

        tripTimes[i] = time() - startTime

        payload, sequenceNum = struct.unpack("!ii", response)

        roundTripTime = str(tripTimes[i]).split(".")
        roundTripTime = "%s.%ss" % (roundTripTime[0], roundTripTime[1][0:4])

        print("Receive sequence num '%d' trip time: %s" % (sequenceNum, roundTripTime))
    except timeout:
        print("Message timed out: %i" % (i))
    except KeyboardInterrupt:
        client.close()
        exit(0)
    else:
        print("Receive data from %s, %d: %s" % (*serverAddress, data.decode()))
        break
