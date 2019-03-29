from datetime import datetime
from os import path

filePath = path.dirname(path.realpath(__file__)) + "/cache.html"
modifiedTime = path.getmtime(filePath)
modifiedTime = datetime.utcfromtimestamp(modifiedTime)
modifiedTime = modifiedTime.strftime("%a, %d %b %Y %H:%M:%S GMT")

print(modifiedTime[0 : len(modifiedTime) - 4])

foo = datetime.strptime(
    modifiedTime[0 : len(modifiedTime) - 4], "%a, %d %b %Y %H:%M:%S"
)

print(foo)
print(datetime.utcnow())
print(datetime.utcnow() > foo)
# print("2019-03-29 16:20:06" > foo)
