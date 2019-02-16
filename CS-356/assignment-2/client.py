from socket import socket, AF_INET, SOCK_DGRAM, timeout
from time import time
import struct
import sys

host = sys.argv[1] if len(sys.argv) >= 2 else "127.0.0.1"
port = int(sys.argv[2]) if len(sys.argv) >= 3 else 3000

# default bufferSize 4096 bytes
bufferSize = 4096

# map of round trip times
tripTimes = []

client = socket(AF_INET, SOCK_DGRAM)
client.settimeout(1)

print("Pinging %s:%d with 8 bytes of data" % (host, port))

numTries = 10
for i in range(1, numTries + 1):
    try:
        # get the current start time
        startTime = time()

        # pack the data using network big endian
        data = struct.pack("!ii", 1, i)

        client.sendto(data, (host, port))

        response, serverAddress = client.recvfrom(bufferSize)

        responseTime = (time() - startTime) * 1000  # time in ms
        tripTimes.append(responseTime)

        sequence = struct.unpack("!ii", response)[1]

        print(
            "Reply from %s:%d, sequence=%d, time=%dms"
            % (host, port, sequence, responseTime)
        )
    except timeout:
        print("Message timed out, sequence=%i" % (i))
    except KeyboardInterrupt:
        client.close()
        exit(0)

print("\nPing statistics for %s:%d" % (host, port))
print(
    "\tPackets: Sent = %d, Received = %d, Lost = %d, (%d percent loss)"
    % (
        numTries,
        len(tripTimes),
        numTries - len(tripTimes),
        round((len(tripTimes) / numTries) * 100),
    )
)
print("Approximate round trip times in milli-seconds")
print(
    "\tMinimum = %dms, Maximum = %dms, Average = %dms"
    % (min(tripTimes), max(tripTimes), round(sum(tripTimes) / len(tripTimes)) * 100)
)

