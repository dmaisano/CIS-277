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
}

# determines the current state of a character, given the previous state
def determineState(char, previousState, index, length):
    char = str(char)
    currentState = ""

    if previousState == state[1] and char.islower():
        previousState = state[1]
        currentState = state[2]

    elif previousState == state[2] and char.islower():
        previousState = state[2]
        currentState = state[2]

    # returns the current state, and new previous state
    return [currentState, previousState]


# print("Project 1 for CS 341")
# print("Semester: Spring 2019")
# print("Written by: Domenico Maisano, dm583")
# print("Instructor: Marvin Nakayama, marvin@njit.edu\n")


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

    print(len(email))

    print("initial state: %s" % (state[1]))

    for charIndex in range(len(email)):
        char = str(email[charIndex])

        currentState, previousState = determineState(
            char, previousState, charIndex, len(email)
        )
        print("currentState: " + currentState)

    # increment index
    index += 2

