# Domenico Maisano

# python script to generate data for the sorting algorithms

import sys
import random

if len(sys.argv) > 1:
    numItems = int(sys.argv[1])
else:
    print("no args")
    exit(1)

f = open("data.txt", "w+")

for i in range(numItems):
    num = random.randint(0, 1000000)

    # f.write("%d\n" % num)

    if (i == numItems - 1):
        f.write("%d" % num)

    else:
        f.write("%d," % num)
