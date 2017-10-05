#import numpy as np

def createMatrix(row, col):
    matrix = []
    for col in range(col): matrix += [[0] * row]
    return matrix

def get_values(data):
  for y in range(col):
    for x in range(row):
      string = "Enter a value for row {0} col {1}: ".format(x + 1, y + 1)
      data[y][x] = int(input(string))

row = int(input("Enter the number of rows for the matrix: "))
col = int(input("Enter the number of columns for the matrix: "))

matrix = createMatrix(row, col)

get_values(matrix)

for y in range(col):
  for x in range(row):
    if (x == 0):
      print("[{0}".format(matrix[y][x]), end=" ")

    elif (x != row - 1):
      print("{0}".format(matrix[y][x]), end=" ")
    
    else:
      print("{0}]".format(matrix[y][x]), end="\n")
