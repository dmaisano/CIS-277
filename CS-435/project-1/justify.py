from typing import List
import re
from sys import argv
from os import isatty


def wordWrap(words: List[str], width: int):
    return "owo"


# def wordWrap(words: List[str], width: int):
#     wrappedText = []
#     # done = false
#     # formattedString = ''

#     line = ""
#     for word in words:
#         if len(line) == width:
#             wrappedText.append(line + "\n")
#             line = word + "_"
#             continue

#         if len(line) + len(word) + 1 <= width:
#             line += word + "_"
#         elif len(line) + len(word) <= width:
#             line += word
#         else:
#             for _ in range(len(line), width):
#                 line += "_"

#     return wrappedText


maxWidth = int(argv[1]) if len(argv) >= 2 else 60

# no stdin
if isatty(0):
    print("missing stdin")
    exit(1)

# read from stdin
words = str(sys.stdin.read()).split()

lines = wordWrap(words, maxWidth)

for line in lines:
    print("length: " + str(len(line)), line)
# print(wordWrap(words, maxWidth))
