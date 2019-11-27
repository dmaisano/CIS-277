"""
Domenico Maisano
Assignment 3
Gradient-Based Classifier 
"""

from typing import List, Dict, Tuple
from operator import itemgetter
from math import inf, isinf, sqrt
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

# trainingSet: Dict[str, List[int]] = {}

trainingSet: List[Tuple[List[int], str]] = []

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

    trainingSet.append((predictiveAttributes, category))
    allPredictiveAttributes.append(predictiveAttributes)

    try:
        categoryCount[category] += 1
    except:
        categoryCount[category] = 1


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
    # trainingSet: Dict[str, List[List[int]]],
    trainingSet: List[Tuple[List[int], str]],
    isRandom: bool,
    history: List[Tuple[int, int]],
    categoryCount: Dict[str, List[int]],
) -> List[Tuple[List[int], str]]:

    # G: Dict[str, List[int]] = {}
    G: List[Tuple[List[int], str]] = []
    copyTrainingSet: List[Tuple[List[int], str]] = []
    # copyTrainingSet: Dict[str, List[List[int]]] = {}
    exemplarVector: List[int] = []

    if isRandom:
        for category, count in categoryCount.items():
            for _ in range(0, count):
                exemplarVector = [
                    randint(minAttr, maxAttr) for (minAttr, maxAttr) in history
                ]

                copyTrainingSet.append((exemplarVector, category))
    else:
        copyTrainingSet = trainingSet

    # calculate the exemplar vectors
    for category, categoryCount in categoryCount.items():
        sumation = []

        for trainingVector, trainingCategory in copyTrainingSet:
            if trainingCategory != category:
                continue

            sumation.append(trainingVector)

        sumation = [sum(x) for x in zip(*sumation)]

        G.append(
            (list(map(lambda num: round(num / categoryCount, 3), sumation)), category)
        )

    return G


# assuming both vectors are of same length
def getDistance(vect1: List[int], vect2: List[int]) -> float:
    dist = 0

    for i in range(len(vect2)):
        dist += pow((vect2[i] - vect1[i]), 2)

    return round(sqrt(dist), 3)


def computeAccuracy(
    G: Dict[str, List[int]], trainingSet: List[Tuple[List[int], str]]
) -> float:
    numCorrect = 0
    
    trainingSetLen = len(trainingSet)

    # contains an training set vector u(Y), it's category, and the distance calculated
    closestExemplar: Tuple[Tuple[List[int], str], float] = ([], 0.0, "")

    for exemplarVector, exemplarCategory in G:
        for vector, category in trainingSet:


    # for exemplarCategory, exemplarVector in G.items():
    #     for i in range(0, trainingSetLength):
    #         category, vectors = trainingSet.items()[i]
    #         vectorsLen = len(vectors)

    #         for j in range(0, vectorsLen):
    #             vector = vectors[j]

    #             newDistance = getDistance(exemplarVector, vector)

    #             print(newDistance)

    #             if i == vectorsLen - 1:
    #                 return 0

    # if i == trainingSetLength - 1:
    #     print(exemplarCategory)

    return numCorrect / trainingSetLen
    return float(0)


def gradDescent(
    # trainingSet: Dict[str, List[List[int]]],
    trainingSet: List[Tuple[List[int], str]],
    stepSize: float,
    epsilon: float,
    M: float,
    isRandom: bool,
    history: List[Tuple[int, int]],
    categoryCount: Dict[str, List[int]],
):
    # G: Dict[str, List[int]] = initializeVectors(
    #     trainingSet, isRandom, history, categoryCount
    # )

    G: List[Tuple[List[int], str]] = initializeVectors(
        trainingSet, isRandom, history, categoryCount
    )

    print(G)

    previousCost = inf
    # computeAccuracy(G, trainingSet)
    # previousAccuracy = computeAccuracy(G, trainingSet)


# print("training set", trainingSet)
# print("\nhistory", history)
# print("\ncategoryCount", categoryCount)
gradDescent(trainingSet, step, epsilon, M, False, history, categoryCount)
