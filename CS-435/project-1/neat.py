from sys import argv, stdin
from os import isatty


def Neat(maxLen: int):
    # exit if no stdin
    if isatty(0):
        print("missing stdin file, please pipe text file")
        exit(1)

    # count = 0
    # result = ""

    # returns the file as a string

    print(len(stdin.read()))

    print(str(stdin.read())[0])
    # for i in range(0, 5):
    #     char = str(stdin.read())[i]

    #     print(char, end="")
    #     # if count <= 60:
    #     #     result += char

    return "owo"


# default value
maxLen = 60

if len(argv) >= 2 and argv[1].isdigit():
    maxLen = int(argv[1])
elif len(argv) >= 2 and not argv[1].isdigit():
    print("using default line length of 60")

Neat(maxLen)

