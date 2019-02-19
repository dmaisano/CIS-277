# Domenico Maisano
# ucid: dm583

import sys
import os


# possible states
state = {
    1: "q1",  # initial state
    2: "q2",
    3: "q3",
    4: "q4",
    5: "q5",
    6: "q6",
    7: "q7",
    8: "q8",
    9: "q9",  # goal state
    "trap": "trap",  # trap state
}

# determines the current state of a character, given the previous state
def determineState(char, previousState):
    char = str(char)
    currentState = ""

    if previousState == state[1] and char.islower():
        currentState = state[2]

    elif previousState == state[2] and char.islower():
        currentState = state[2]

    elif previousState == state[2] and char == ".":
        currentState = state[3]

    elif previousState == state[3] and char.islower():
        currentState = state[2]

    elif previousState == state[2] and char == "@":
        currentState = state[4]

    elif previousState == state[4] and char.islower():
        currentState = state[5]

    elif previousState == state[5] and char.islower():
        currentState = state[5]

    elif previousState == state[5] and char == ".":
        currentState = state[6]

    elif previousState == state[6] and char != "c" and char.lower():
        currentState = state[5]

    elif previousState == state[6] and char == "c":
        currentState = state[7]

    # .c.
    elif previousState == state[7] and char == ".":
        currentState = state[6]

    elif previousState == state[7] and char != "o" and char.lower():
        currentState = state[5]

    elif previousState == state[7] and char == "o":
        currentState = state[8]

    # .co.
    elif previousState == state[8] and char == ".":
        currentState = state[6]

    elif previousState == state[8] and char != "m" and char.islower():
        currentState = state[5]

    # reached goal state
    elif previousState == state[8] and char == "m":
        currentState = state[9]

    # .com.
    elif previousState == state[9] and char == ".":
        currentState = state[6]

    # anything else results in being stuck in the self looping trap case
    else:
        currentState = state["trap"]

    # returns the current state
    return currentState


# create the output file
fileName = sys.argv[1] if len(sys.argv) >= 2 else "output.txt"
outputFile = open(fileName, "w")


print("Project 1 for CS 341")
outputFile.write("Project 1 for CS 341\n")
print("Semester: Spring 2019")
outputFile.write("Semester: Spring 2019\n")
print("Written by: Domenico Maisano, ucid dm583")
outputFile.write("Written by: Domenico Maisano, ucid dm583\n")
print("Instructor: Marvin Nakayama, marvin@njit.edu")
outputFile.write("Instructor: Marvin Nakayama, marvin@njit.edu\n")


# no stdin
if os.isatty(0):
    exit(1)

# read from stdin
stdin = str(sys.stdin.read()).splitlines()

# starting position of list
index = 0

while index < len(stdin):
    previousState = "q1"

    email = str(stdin[index + 1]) if stdin[index] == "y" else exit(0)

    print("\nevaluating email: " + email)
    outputFile.write("\nevaluating email: %s\n" % email)
    print("initial state: q1")
    outputFile.write("initial state: q1\n")

    for charIndex in range(len(email)):
        char = str(email[charIndex])

        currentState = determineState(char, previousState)
        previousState = currentState
        print("%s, state: %s" % (char, currentState))
        outputFile.write("%s, state: %s\n" % (char, currentState))

        if charIndex == len(email) - 1 and currentState == "q9":
            print("%s is a valid email" % email)
            outputFile.write("%s is a valid email\n" % email)
        elif charIndex == len(email) - 1 and currentState != "q9":
            print("%s is not a valid email" % email)
            outputFile.write("%s is not a valid email\n" % email)

    # increment index
    index += 2

