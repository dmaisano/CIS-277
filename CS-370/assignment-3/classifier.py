"""
Domenico Maisano
Assignment 3
Gradient-Based Classifier 
"""

from typing import List, Dict, Tuple
from operator import itemgetter
from math import inf, isinf
from random import randint
from os import path
import argparse


parser = argparse.ArgumentParser(description="Gradient-Based Classifier Program")

# positional args
parser.add_argument(
    "file", type=str, default="", help="relative input file path",
)
parser.add_argument("step", action="store", type=float, help="step size")
parser.add_argument("epsilon", action="store", type=float, help="epsilon")
parser.add_argument("M", action="store", type=int, help="number of random restarts")

# optional verbose arg
parser.add_argument(
    "-v", "--verbose", action="store_true", default=False, help="verbose output flag"
)

args = parser.parse_args()

file, step, epsilon, M, verbose = itemgetter("file", "step", "epsilon", "M", "verbose")(
    vars(args)
)

if M < 0:
    print("setting M (random restarts) to zero")
    M = 0

inputFile: List[str] = open(file, "r").readlines()

trainingSet: Dict[str, List[int]] = {}

# contains the min and max value of each predictive attribute in u(X)
history: List[Tuple[int, int]] = []

# number of particular categories in the given training set
categoryCount: Dict[str, List[int]] = {}

# used to keep trakc of all u(Y) vectors
allPredictiveAttributes: List[List[int]] = []

line: str
for line in inputFile:
    line: List[str] = line.strip().split(",")
    category = line.pop().strip()

    # u(Y), vector of predictive attributes
    predictiveAttributes: List[int] = list(map(int, line))

    if category in trainingSet.keys():
        trainingSet[category].append(predictiveAttributes)
        categoryCount[category] += 1
    else:
        trainingSet[category] = [predictiveAttributes]
        categoryCount[category] = 1

    allPredictiveAttributes.append(predictiveAttributes)

# transpose the matrix of predictive attributes
# reference: https://www.geeksforgeeks.org/transpose-matrix-single-line-python/
transposedMatrix = list(zip(*allPredictiveAttributes))

# now we can simply iterate over the transposed matrix and get the min and max of each row
# print(transposedMatrix)
for row in transposedMatrix:
    history.append((min(row), max(row)))


# print helper function
def printVerbose(obj):
    if verbose:
        print(obj)


def initializeVectors(
    trainingSet: Dict[str, List[List[int]]],
    isRandom: bool,
    history: List[Tuple[int, int]],
    categoryCount: Dict[str, List[int]],
):
    def appendExemplar(copyTrainingSet, category, exemplarVector):
        # try / catch is more performant than manually checking if the key in dict exists
        try:
            copyTrainingSet[category].append(exemplarVector)
        except:
            copyTrainingSet[category] = [exemplarVector]

    G: Dict[str, List[int]] = {}
    copyTrainingSet: Dict[str, List[List[int]]] = {}
    exemplarVector: List[int] = []

    if isRandom:
        for category, count in categoryCount.items():
            for _ in range(0, count):
                exemplarVector = [
                    randint(minAttr, maxAttr) for (minAttr, maxAttr) in history
                ]
                appendExemplar(copyTrainingSet, category, exemplarVector)
    else:
        copyTrainingSet = trainingSet

    # calculate the exemplar vectors
    for category, vectors in copyTrainingSet.items():
        sumation = [sum(x) for x in zip(*vectors)]
        G[category] = list(map(lambda num: round(num / len(vectors), 3), sumation))

    return G


def computeAccuracy(G: Dict[str, List[int]], trainingSet: Dict[str, List[List[int]]]):
    print("owo")


def gradDescent(
    trainingSet: Dict[str, List[List[int]]],
    stepSize: float,
    epsilon: float,
    M: float,
    isRandom: bool,
    history: List[Tuple[int, int]],
    categoryCount: Dict[str, List[int]],
):
    G: Dict[str, List[int]] = initializeVectors(
        trainingSet, isRandom, history, categoryCount
    )

    prevCost = inf

    print(G)


# print("training set", trainingSet)
# print("\nhistory", history)
# print("\ncategoryCount", categoryCount)
gradDescent(trainingSet, step, epsilon, M, False, history, categoryCount)
