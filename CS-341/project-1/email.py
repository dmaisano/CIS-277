# Domenico Maisano
# ucid: dm583

import sys
import os


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

states = {1: "q1", 2: "q2", 3: "q3"}
currentState = "start"
previousState = ""

while index < len(stdin):
    email = str(stdin[index + 1]) if stdin[index] == "y" else exit(0)

    # print(range(len(email)))

    for charIndex in range(len(email)):
        char = str(email[charIndex])

        # check if state == q3
        if char == "." and (charIndex + 3 <= len(email)):
            currentState = states[3]
            print(currentState)

        # if char.islower():
        # currentState = ""

    # increment index
    index += 2
