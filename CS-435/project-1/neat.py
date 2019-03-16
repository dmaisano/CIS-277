import sys
import os

# return the optimal line
def giveLines(words: "List[str]", maxLength: int, index: int) -> "List":
    # initialIndex = index
    res = ""
    currentLength = 0

    while currentLength <= maxLength:
        word = words[index]

        if currentLength == maxLength:
            break

        if currentLength + len(word) + 1 <= maxLength:
            res += word + "_"
            currentLength += len(word) + 1
            index += 1
        elif currentLength + len(word) <= maxLength:
            res += word
            currentLength += len(word)
            index += 1
        else:
            print(res, end=" ")
            print("length: " + str(currentLength))
            print(maxLength - currentLength)

            for x in range(0, maxLength - currentLength):
                res += "_"
                currentLength += 1

            # for i in range(1, maxLength - currentLength):
            #     res += " "
            #     currentLength += 1

    return [maxLength, index, res]


# def giveLines(words: "List[str]", int maxLength):
# return []


maxLength = int(sys.argv[1]) if len(sys.argv) >= 2 else 60

# no stdin
if os.isatty(0):
    print("missing stdin")
    exit(1)

# read from stdin
words = str(sys.stdin.read()).split()

index = 0

print(giveLines(words, maxLength, index))

# test1, test2, test3, test4 = giveLines(words, maxLength, index)

# print(test1)
# print(test2)
# print(test3)
# print(test4)

# print(giveLines(words, maxLength, 0))


# while (giveLines(words, maxLength)):

