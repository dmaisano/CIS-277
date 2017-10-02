class Matrix:
  def __init__(self):
    self.name = self.get_name()
    self.size = self.get_size()
    self.row = self.size[0]
    self.col = self.size[1]
    self.matrix = [ list(range(self.row)), list(range(self.col)) ] # initializes matrix with default values
    self.get_values()
    print() # prints a new line at the end of object construction

  # Returns the name for the matrix as per user input
  def get_name(self):
    name = input("Enter the name for the matrix: ")

    return name

  # Retuns a list of the rows and cols for the matrix
  def get_size(self):
    size = []
    size.append(int(input("Enter the number of rows for matrix {0}: ".format(self.name))))
    size.append(int(input("Enter the number of columns for matrix {0}: ".format(self.name))))

    return size

  # Gets values for the matrix as per user input
  def get_values(self):
    for x in range(self.row):
      for y in range(self.col):
        string = "Enter a value for row {0} col {1}: ".format(x, y)
        num = int(input(string))
        self.matrix[x][y] = num

  # Prints the values of the matrix
  def printMatrix(self):
    print("Matrix " + self.name + ":")

    for x in range(self.row):
      for y in range(self.col):
        if(y == 0):
          print("[{0}".format(self.matrix[x][y]), end=" ")
        
        else:
          print("{0}]".format(self.matrix[x][y]), end="\n")

matrices = []

toast = Matrix()
matrices.append(toast)

for matrix in matrices:
  matrix.printMatrix()

print("\n")
