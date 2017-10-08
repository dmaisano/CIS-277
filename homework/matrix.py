# import numpy as np

def createMatrix(row, col):
  matrix = []
  for col in range(col): matrix += [[0] * row]

  return matrix

class Matrix:
  def __init__(self, row=None, col=None, name=None, data=None):
    self.name = name
    self.row = row
    self.col = col

    if data == None:
      self.data = createMatrix(self.row, self.col)
    
    else:
      self.data = data

    self.get_name()
    self.get_size()
    #self.get_values()
    #print() # prints a new line at the end of object construction

  # Returns the name for the matrix as per user input
  def get_name(self):
    if (self.name == None):
      self.name = input("Enter the name for the matrix: ")

    else:
      pass

  # Retuns a list of the rows and cols for the matrix
  def get_size(self):
    
    if(self.row == None and self.col == None):
      self.row = int(input("Enter the number of rows for matrix {0}: ".format(self.name)))
      self.col = int(input("Enter the number of columns for matrix {0}: ".format(self.name)))

    # pass because row & col have already been defined
    else:
      pass

  # Gets values for the matrix as per user input
  def get_values(self):
    for y in range(self.col):
      for x in range(self.row):
        string = "Enter a value for col {0} row {1}: ".format(y + 1, x + 1)
        self.data[y][x] = int(input(string))

    print()

  # Prints the values of the matrix
  def printMatrix(self):
    print("\nMatrix {0}:".format(self.name))

    for y in range(self.col):
      for x in range(self.row):
        if (x == 0):
          print("[{0}".format(self.data[y][x]), end=" ")

        elif (x != self.row - 1):
          print("{0}".format(self.data[y][x]), end=" ")
        
        else:
          print("{0}]".format(self.data[y][x]), end="\n")

  def __add__(self, other):
    if (self.row == other.row and self.col == other.col):
      values = createMatrix(self.row, self.col)

      for y in range(self.col):
        for x in range(self.row):
          values[y][x] = self.data[y][x] + other.data[y][x]

      return Matrix(self.row, self.col, None, values)

    else:
      print("Cannot add the two matrices. Please make sure they are the same size!")

  def __sub__(self, other):
    if (self.row == other.row and self.col == other.col):
      values = createMatrix(self.row, self.col)

      for y in range(self.col):
        for x in range(self.row):
          values[y][x] = self.data[y][x] - other.data[y][x]

      return Matrix(self.row, self.col, None, values)

    else:
      print("Cannot subtract the two matrices. Please make sure they are the same size!")

matrices = []

toast = Matrix(4, 2)
toast.get_values()
eggs = Matrix(4, 2)
eggs.get_values()

sumMatrices = toast + eggs

matrices.append(toast)
matrices.append(eggs)
matrices.append(sumMatrices)

for matrix in matrices:
  # print("\n", matrix.data)
  matrix.printMatrix()

print("\n")
