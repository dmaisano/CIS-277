from os import path
from datetime import datetime

filePath: str = path.dirname(path.realpath(__file__)) + "/sample.html"

lastModified = path.getmtime(filePath)
lastModified = datetime.utcfromtimestamp(lastModified).replace(microsecond=0)

print(type(lastModified))
print(lastModified)
