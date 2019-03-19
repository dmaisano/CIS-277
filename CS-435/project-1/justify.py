from typing import List
import sys
import os


def solveCost(arr: List[int], width: int) -> List[List[int], List[int]]:
    n = len(arr)

    # initialize a list of size n
    dp = [0] * n

    # used to store the index of the last word in each line
    ans = [0] * n

    # if only one word is present, then the cost of the last line is zero
    dp[n - 1] = 0
    ans[n - 1] = n - 1

    # ???
    for i in range(n - 2, -1, -1):
        currentLen = -1
        dp[i] = sys.maxsize

        # add words to the current line
        for j in range(i, n):
            currentLen += arr[j] + 1

            # can't fit more words on currentLine
            if currentLen > width:
                break
            if j == n - 1:
                cost = 0
            else:
                cost = (width - currentLen) ** 3

            # check if this arrangement gives the min cost
            if cost < dp[i]:
                dp[i] = cost
                ans[i] = j

    i = 0
    boundaries = []
    while i < n:
        boundaries.append([i, ans[i]])

        # set the new index to the next word
        i = ans[i] + 1

    return boundaries


def printNeat(words: List[str], boundaries: List[List[int], List[int]]):
    for i, j in boundaries:
        for index in range(i, j):
            print(words[index], end=" ")

        print()


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

    solveCost(wordLengths, maxWidth)

