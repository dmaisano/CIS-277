"""
Domenico Maisano
Assignment 3
Gradient-Based Classifier 
"""

from typing import List, Dict, Tuple
from operator import itemgetter
from math import inf, isinf, sqrt
from random import randint
from json import dumps
from os import path
import argparse


parser = argparse.ArgumentParser(description="Gradient-Based Classifier Program")

# positional args
parser.add_argument(
    "file", type=str, default="", help="relative input file path",
)
parser.add_argument("step", action="store", type=float, help="step size")
parser.add_argument("epsilon", action="store", type=float, help="epsilon")
parser.add_argument("M", action="store", type=float, help="M")
parser.add_argument(
    "numRestarts", action="store", type=int, help="number of random restarts"
)

# optional verbose arg
parser.add_argument(
    "-v", "--verbose", action="store_true", default=False, help="verbose output flag"
)

args = parser.parse_args()

file, step, epsilon, M, numRestarts, verbose = itemgetter(
    "file", "step", "epsilon", "M", "numRestarts", "verbose"
)(vars(args))

if numRestarts < 0:
    print("setting random restarts to zero")
    numRestarts = 0

inputFile: List[str] = open(file, "r").readlines()

trainingSet: List[Tuple[List[float], str]] = []

# contains the min and max value of each predictive attribute in u(X)
history: List[Tuple[float, float]] = []

# number of particular categories in the given training set
categoryCount: Dict[str, List[float]] = {}

# used to keep trakc of all u(Y) vectors
allPredictiveAttributes: List[List[float]] = []

line: str
for line in inputFile:
    line: List[str] = line.strip().split(",")
    category = line.pop().strip()

    # u(Y), vector of predictive attributes
    uY: List[float] = list(map(float, line))

    trainingSet.append((uY, category))
    allPredictiveAttributes.append(uY)

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
def printVerbose(obj, sep=None):
    if verbose == True and sep == None:
        print(obj)
    elif verbose == True:
        try:
            print(obj, sep=sep)
        except:
            print(obj)


def initializeVectors(
    trainingSet: List[Tuple[List[float], str]],
    isRandom: bool,
    history: List[Tuple[float, float]],
    categoryCount: Dict[str, List[float]],
) -> Dict[str, List[float]]:

    G: Dict[str, List[float]] = {}
    copyTrainingSet: List[Tuple[List[float], str]] = []
    exemplarVector: List[float] = []

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

        G[category] = list(map(lambda num: num / categoryCount, sumation))

    return G


# assuming both vectors are of same length
def distSquared(vect1: List[float], vect2: List[float]) -> float:
    dist = 0

    for i in range(len(vect2)):
        dist += pow((vect1[i] - vect2[i]), 2)
    return dist


# returns an exemplar vector from G that is closest to uY
def calcClosestExemplar(uY: List[float], G: Dict[str, List[float]]) -> object:
    # contains an training set vector u(Y), it's category, and the distance calculated
    closestExemplar = {"exemplar": [], "distance": inf, "category": ""}

    for exemplarCategory, exemplarVector in G.items():
        dist = distSquared(exemplarVector, uY)

        # assuming no ties
        if dist < closestExemplar["distance"]:
            closestExemplar = {
                "exemplar": exemplarVector,
                "distance": dist,
                "category": exemplarCategory,
            }

    return closestExemplar


def computeAccuracy(
    G: Dict[str, List[float]], trainingSet: List[Tuple[List[float], str]]
) -> float:
    numCorrect = 0

    trainingSetLen = len(trainingSet)

    for vector, category in trainingSet:
        closestExemplar = calcClosestExemplar(vector, G)

        if closestExemplar["category"] == category:
            numCorrect += 1

    return numCorrect / trainingSetLen


def exitGradDescent(accuracies: List[float], converged=False, lastAccuracy=0.0):
    if converged == True:
        printVerbose("Converged. Accuracy: %.4f" % lastAccuracy)

    printVerbose("\nBest Accuracy: %.4f" % (max(accuracies)))


def gradDescent(
    trainingSet: List[Tuple[List[float], str]],
    stepSize: float,
    epsilon: float,
    M: float,
    isRandom: bool,
    history: List[Tuple[float, float]],
    categoryCount: Dict[str, List[int]],
    previousCost=inf,
    currentIteration=0,
    previousAccuracy=0.0,
    accuracies: List[float] = [],
) -> Dict[str, List[float]]:
    G: Dict[str, List[float]] = initializeVectors(
        trainingSet, isRandom, history, categoryCount
    )

    if currentIteration == numRestarts:
        exitGradDescent(accuracies, True)
        return G

    printVerbose("Iteration: %d" % currentIteration)
    for _, g_v in G.items():
        printVerbose(", ".join(("%.3f" % num) for num in g_v))

    accuracy = computeAccuracy(G, trainingSet)
    accuracies.append(accuracy)
    printVerbose("Accuracy: %.4f\n" % accuracy)

    totalCost = 0

    n = {}
    for v, _ in G.items():
        n[v] = []

    # for each datapoint "Y" in T
    # ? u(Y) == vector of predictive attribues
    # ?    v == category
    for uY, v in trainingSet:
        # find g_w closest to u(Y)
        g_w, w = [calcClosestExemplar(uY, G)[key] for key in ("exemplar", "category")]

        # failed to classify u(Y) correctly
        if w != v:
            g_v = G[v]

            cost = distSquared(g_v, uY) - distSquared(uY, g_w)

            if cost < M:
                n[v] = [x - y for x, y in zip(uY, g_v)]
                n[w] = [x - y for x, y in zip(g_w, uY)]
                totalCost += cost
            else:
                totalCost += M

    if totalCost < epsilon:
        exitGradDescent(accuracies)
        return G  # training complete

    if not isinf(previousCost) and totalCost > ((1 - epsilon) * previousCost):
        exitGradDescent(accuracies)
        return G  # improvement too small

    h = {}
    for v, g_v in G.items():
        h[v] = [x - y for x, y in zip(uY, g_v)]

    newAccuracy = computeAccuracy(h, trainingSet)

    if newAccuracy < accuracy:
        exitGradDescent(accuracies)
        return G

    currentIteration += 1
    return gradDescent(
        trainingSet,
        step,
        epsilon,
        M,
        True,
        history,
        categoryCount,
        totalCost,
        currentIteration,
        newAccuracy,
        accuracies,
    )


gradDescent(trainingSet, step, epsilon, M, False, history, categoryCount)
