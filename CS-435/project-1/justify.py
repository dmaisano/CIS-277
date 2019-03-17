from typing import List
import os
import re
import sys


def wordWrap(text: str, width: int):
    wrappedText = ""
    # line = ""

    return wrappedText


# def wordWrap(words: List[str], width: int):
#     wrappedText = []
#     # done = false
#     # formattedString = ''

#     line = ""``
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


maxWidth = int(sys.argv[1]) if len(sys.argv) >= 2 else 60

# no stdin
if os.isatty(0):
    print("missing stdin")
    exit(1)

# read from stdin
# words = str(sys.stdin.read()).split()
text = sys.stdin.read()

lines = wordWrap(text, maxWidth)
