from typing import Any, List
import sys
import os

# returns a list of boundaries for where lines begin and end
def justifyText(words: List[str], width: int) -> List[Any]:
    n = len(words)

    # memo
    costs = [0] * n

    # list containing the indices of the last words for each line
    finalWords = [0] * n

    # initial value
    # if there is only one word in the list, default cost is zero
    costs[n - 1] = 0
    finalWords[n - 1] = n - 1

    # Make each word first word of line
    # by iterating over each index in arr.
    for i in range(n - 2, -1, -1):
        # offset one because of spaces added after each word
        lineLength = -1

        # default to infinity
        costs[i] = 2147483647

        # consider (n - i) possibilities
        for j in range(i, n):
            wordLength = len(words[j])

            lineLength += wordLength + 1

            # word cannot fit on line
            if lineLength > width:
                break

            # found the last word that fits on the final line
            # (cost of last line is zero)
            if j == n - 1:
                cost = 0
            else:
                cost = (width - lineLength) ** 3 + costs[j + 1]

            # check if arragement is optimal
            if cost < costs[i]:
                costs[i] = cost
                finalWords[i] = j
    i = 0
    bounds = []
    while i < n:
        bounds.append([i, finalWords[i] + 1])
        i = finalWords[i] + 1

    return bounds


# print the total cost, along with the formatted text
def printNeat(words: List[str], bounds: List[any], width: int):
    text = ""

    totalCost = 0

    for bound in range(0, len(bounds)):
        i = bounds[bound][0]
        j = bounds[bound][1]

        # line consists of words(i, j)
        line = " ".join(words[i:j])

        # exclude last line as to not affect sum of cubes
        if bound != len(bounds) - 1:
            cost = (width - len(line)) ** 3
            totalCost += cost

        text += line + "\n"

    print(totalCost)
    print(text)


if __name__ == "__main__":
    # get max length from cli arg or default to 60
    maxWidth = int(sys.argv[1]) if len(sys.argv) >= 2 else 60

    # no stdin
    if os.isatty(0):
        exit(1)

    # get the list of words from stdin
    words = str(sys.stdin.read()).split()

    bounds = justifyText(words, maxWidth)

    printNeat(words, bounds, maxWidth)

