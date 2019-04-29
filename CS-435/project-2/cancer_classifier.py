from math import floor
from sys import argv

import numpy as np
from scipy.optimize import linprog

malig = argv[1] if len(argv) >= 2 else "./malig.txt"
benign = argv[2] if len(argv) >= 3 else "./benign.txt"

maligData = []
benignData = []

# read the first 100 lines of malig data for the classifier
with open(malig, "r") as f:
    f = f.read().splitlines()[:100]

    for line in f:
        maligData += list(map(float, line.split(",")[1:]))

# read the first 200 lines of benign data for the classifier
with open(benign, "r") as f:
    f = f.read().splitlines()[:200]

    for line in f:
        benignData += list(map(float, line.split(",")[1:]))

# 30 floating point values per line
p = floor(len(maligData) / 30)  # 100
q = floor(len(benignData) / 30)  # 200

foo = np.zeros([10, 10])
print(foo)
