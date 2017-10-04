def squareNum(num=None):
  
  if (num == None):
    temp = input("Enter a number: ")

  else:
    temp = num

    temp *= temp

    print("Square of number is '{0}'".format(temp))

squareNum(10)
