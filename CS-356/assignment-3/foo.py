import os
from datetime import datetime

# print formatdate(timeval=None, localtime=False, usegmt=True)

timestamp = os.path.getmtime("sample.html")

print(timestamp)

timestamp = datetime.utcfromtimestamp(timestamp).strftime("%a, %d %b %Y %H:%M:%S GMT")
print(timestamp)

