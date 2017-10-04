class Matrix:
  def __init__(self, row=None, col=None, name=None):
    self.name = name
    self.row = row
    self.col = col
    self.get_name()
    self.get_size()
    self.matrix = [] # initializes matrix with default values
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
    self.matrix = [ list(range(self.row)), list(range(self.col)) ]

    for x in range(self.row):
      for y in range(self.col):
        string = "Enter a value for row {0} col {1}: ".format(x, y)
        num = int(input(string))
        self.matrix[x][y] = num

    print()

  # Prints the values of the matrix
  def printMatrix(self):
    print("Matrix {0}:".format(self.name))

    for x in range(self.row):
      for y in range(self.col):
        if(y == 0):
          print("[{0}".format(self.matrix[x][y]), end=" ")
        
        else:
          print("{0}]".format(self.matrix[x][y]), end="\n")

  def __add__(self, other):
    if (self.row == other.row and self.col == other.col):
      m = Matrix(self.name, self.row, self.col)

      m.matrix = [ list(range(self.row)), list(range(self.col)) ]

      for x in range(self.row):
        for y in range(self.col):
          m.matrix[x][y] = self.matrix[x][y] + other.matrix[x][y]

      return m

    else:
      print("Cannot add the two matrices. Please make sure they are the same size!")

matrices = []

toast = Matrix(2, 2)
toast.get_values()
eggs = Matrix(2, 2)
eggs.get_values()

m = Matrix(2, 2)

m = toast + eggs

matrices.append(toast)
matrices.append(eggs)

for matrix in matrices:
  matrix.printMatrix()

print("\n")
