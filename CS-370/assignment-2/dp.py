# https://gist.github.com/davefernig/e670bda722d558817f2ba0e90ebce66f
from sys import argv
from os import path


def main():
    print(argv)

    if len(argv) < 1:
        print("missing input file")
        exit(-2)

    fileName = argv[1]
    filePath = path.join(path.dirname(path.abspath(__file__)), fileName)
    print(fileName)
    print(filePath)

    extraLines = []

    S = {}
    V = {}

    sawZero = False
    for line in open(filePath, "r"):
        print(line)


main()
