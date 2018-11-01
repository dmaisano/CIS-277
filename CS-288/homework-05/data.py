# python script to generate unique data for the sorting algorithms

import sys
import random

size = 100000000

if len(sys.argv) > 1:
    size = int(sys.argv[1])

data = random.sample(range(size), size)

dataFile = open("data.txt", "w")

print("populating data.txt with %d integers" % size)

for i in data:
    dataFile.write(str(i) + "\n")
