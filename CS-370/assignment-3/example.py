from math import pow

def addVector(a, b):
    return list(map(sum, zip(a, b)))


def examplarVector(classificationVectors):
    sumation = classificationVectors[0]

    for vector in classificationVectors[1:]:
        sumation = addVector(sumation, vector)

    return list(
        map(lambda num: round(num * 1 / len(classificationVectors), 3), sumation)
    )


def examplarDistance(z, vector):
    dist = 0

    for i in range(len(z)):
        dist += pow((z[i] - vector[i]), 2)

    return round(dist, 3)


a = [
    [1, 1, 2],
    [2, 1, 1],
    [2, 0, 1]
]

b = [
    [0, 1, 2],
    [3, 2, 0],
]

c = [
    [3, 3, 0],
    [0, 3, 0],
    [3, 2, 1],
    [0, 3, 3],
]

ga = examplarVector(a)
gb = examplarVector(b)
gc = examplarVector(c)

z = [2, 2, 2]

distGA = examplarDistance(z, ga)
distGB = examplarDistance(z, gb)
distGC = examplarDistance(z, gc)

print(distGA)
print(distGB)
print(distGC)

print("objective function result:", round(distGA + distGB + distGC, 3))
