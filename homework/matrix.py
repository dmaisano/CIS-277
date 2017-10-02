class Matrix:
  def __init__(self, name, row, col):
    self.name = name
    self.row = row
    self.col = col
    self.matrix = [ list(range(row)), list(range(col)) ] # initializes matrix with default values
    self.get_values()
    print()

  
  def get_values(self):
    for x in range(self.row):
      for y in range(self.col):
        string = "Enter a value for row {0} col {1}: ".format(x, y)
        num = int(input(string))
        self.matrix[x][y] = num

  def printMatrix(self):
    print("Matrix " + self.name + ":")

    for x in range(self.row):
      for y in range(self.col):
        if(y == 0):
          print("[{0}".format(self.matrix[x][y]), end=" ")
        
        else:
          print("{0}]".format(self.matrix[x][y]), end="\n")

toast = Matrix("toast", 2, 2)

toast.printMatrix()

print("\n")
