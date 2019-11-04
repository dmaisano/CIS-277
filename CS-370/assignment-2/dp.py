# https://gist.github.com/davefernig/e670bda722d558817f2ba0e90ebce66f
from typing import List
from sys import argv
from os import path
from json import dumps


class Literal:
    def __init__(self, literal: str):
        self.literal: str = literal


def main():
    if len(argv) < 1:
        print("missing input file")
        exit(-2)

    fileName = argv[1]
    filePath = path.join(path.dirname(path.abspath(__file__)), fileName)

    S = []
    V = {}

    extraLines = []
    sawZero = False

    line: str
    for line in open(filePath, "r").readlines():
        if not sawZero:
            line = line.strip()
        else:
            extraLines.append(line)
            continue

        if line == "0":
            sawZero = True
            continue

        clause: List[Literal] = []
        for literal in line.split():
            clause.append(literal)

        S.append(clause)

    for clause in S:
        print(clause)


main()
