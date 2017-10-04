'''
def squareNum(num=None):
  
  if (num == None):
    temp = input("Enter a number: ")

  else:
    temp = num

    temp *= temp

    print("Square of number is '{0}'".format(temp))

squareNum(10)
'''

def createMatrix(row=None, col=None):
  if(row == None and col == None):
    row = input("Enter the rows for the list: ")
    col = input("Enter the columns for the list: ")

  matrix = [ list(range(row)), list(range(col, col*2)) ]

  return matrix

'''
def getValues(matrix):
  for x in range(matrix[0]):
    for y in range(matrix[1]):
      string = "Enter a value for row {0} col {1}: ".format(x, y)
      matrix[x][y] = int(input(string))
'''
matrix = createMatrix(3, 3)

for x in matrix:
  for y in x:
    print(x)

print()

for x in matrix:
  for y in x:
    print(y)

#getValues(matrix)


