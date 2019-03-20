from typing import Any, List
import sys
import os


def justifyText(arr: List[int], width: int) -> List[Any]:
    n = len(arr)

    costs = [0] * n

    # Array in which finalWords[i] store index
    # of last word in line starting with
    # word arr[i].
    finalWords = [0] * n

    # If only one word is present then
    # only one line is required. Cost
    # of last line is zero. Hence cost
    # of this line is zero. Ending point
    # is also n-1 as single word is
    # present.
    costs[n - 1] = 0
    finalWords[n - 1] = n - 1

    # Make each word first word of line
    # by iterating over each index in arr.
    for i in range(n - 2, -1, -1):
        lineLength = -1
        costs[i] = 2147483647

        # Keep on adding words in current
        # line by iterating from starting
        # word upto last word in arr.
        for j in range(i, n):

            # Update number of characters
            # in current line. arr[j] is
            # number of characters in
            # current word and 1
            # represents space character
            # between two words.
            lineLength += arr[j] + 1

            # If limit of characters
            # is violated then no more
            # words can be added to
            # current line.
            if lineLength > width:
                break

                # If current word that is
                # added to line is last
                # word of arr then current
                # line is last line. Cost of
                # last line is 0. Else cost
                # is square of extra spaces
                # plus cost of putting line
                # breaks in rest of words
                # from j+1 to n-1.
            if j == n - 1:
                cost = 0
            else:
                cost = (width - lineLength) * (width - lineLength) + costs[j + 1]

                # Check if this arrangement gives
                # minimum cost for line starting
                # with word arr[i].
            if cost < costs[i]:
                costs[i] = cost
                finalWords[i] = j

                # Print starting index and ending index
                # of words present in each line.
    i = 0
    bounds = []
    while i < n:
        if i != 0:
            bounds.append([i + 1, finalWords[i] + 1])
        elif i == 0:
            bounds.append([i, finalWords[i] + 1])
        i = finalWords[i] + 1

    return bounds


def printNeat(words: List[str], bounds: List[any], width: int):
    text = ""

    totalCost = 0

    line = ""
    for bound in bounds:
        i = bound[0]
        j = bound[1]
        # print(i, j, range(i, j))
        for index in range(i, j):
            word = words[index]

            if index != j - 1:
                line += word + " "
            else:
                if len(line) == 60:
                    line += word + "\n"
                else:
                    cost = width - len(line) + len(word)
                    print("cost", cost)
                    totalCost += cost
                    line += word + "\n"

            text += line
            line = ""

    # print(cost)
    print(text)


if __name__ == "__main__":
    # get max length from cli arg or default to 60
    maxWidth = int(sys.argv[1]) if len(sys.argv) >= 2 else 60

    # no stdin
    if os.isatty(0):
        exit(1)

    # get the list of words from stdin
    words = str(sys.stdin.read()).split()

    # list containing int lengths of each word
    wordLengths = []

    # append the length to the list
    for word in words:
        wordLengths.append(len(word))

    # solveWordWrap(wordLengths, maxWidth)
    bounds = justifyText(wordLengths, maxWidth)
    # print(bounds)
    printNeat(words, bounds, maxWidth)

