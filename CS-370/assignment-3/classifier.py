"""
Domenico Maisano
Assignment 3
Gradient-Based Classifier 
"""

from typing import List, Dict, Tuple
from operator import itemgetter
from sys import argv
import argparse
from os import path
from math import inf, isinf


parser = argparse.ArgumentParser(description="Gradient-Based Classifier Program")

parser.add_argument(
    "file", type=str, default="", help="relative input file path",
)
parser.add_argument("step", action="store", type=float, help="step size")
parser.add_argument("epsilon", action="store", type=float, help="epsilon")
parser.add_argument("M", action="store", type=int, help="number of random restarts")
parser.add_argument(
    "-v", "--verbose", action="store_true", default=False, help="verbose output flag"
)

args = parser.parse_args()

file, step, epsilon, M, verbose = itemgetter("file", "step", "epsilon", "M", "verbose")(
    vars(args)
)

inputFile: List[str] = open(file, "r").readlines()

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
    for category, attributeList in trainingSet.items():
        print(category)

    return {}


def gradDescent(
    trainingSet: Dict[str, List[int]], stepSize: float, epsilon: float, M: float
):
    G = initializeVectors(trainingSet)
    print("gradDescent")


gradDescent(trainingSet, step, epsilon, M)
