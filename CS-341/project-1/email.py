import sys
import os


def emailHandler():
    message = ""

    # no stdin
    if os.isatty(0):
        message = input("Enter a message: ")

    # read from stdin
    else:
        message = sys.stdin.read()

    print(message)


emailHandler()
