"""
Domenico Maisano
Assignment 3
Gradient-Based Classifier 
"""

from typing import List, Dict, Tuple
from sys import argv
from os import path
from math import inf, isinf


if len(argv) < 2:
    print("Missing input file arg")
    exit(1)

verboseMode = True if "-v" or "--verbose" in argv else False

# assuming path is relative
filePath: str = argv[1]

inputFile: List[str] = open(filePath, "r").readlines()

trainingSet: Dict[str, List[int]] = {}

line: str
for line in inputFile:
    line = line.strip().split(",")
    category = line.pop()

    predictiveAttributes: List[int] = []

    for attr in line:
        predictiveAttributes.append(int(attr))

    if category in trainingSet.keys():
        trainingSet[category].append(predictiveAttributes)
    else:
        trainingSet[category] = [predictiveAttributes]


def initializeVectors(trainingSet: Dict[str, List[int]]):
    print("initializeVectors")

    return {}


def gradDescent(
    trainingSet: Dict[str, List[int]], stepSize: float, epsilon: float, M: float
):
    G = initializeVectors(trainingSet)
    print("gradDescent")


stepSize = 0
epsilon = 0
M = 0

gradDescent(trainingSet, stepSize, epsilon, M)
