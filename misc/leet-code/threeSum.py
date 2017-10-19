def threeSum(arr):
  arr.sort() # returns a sorted array of numbers
  triplets = []

  for i in range(len(arr)-2):
    if i > 0 and arr[i] == arr[i-1]:
      continue

    # left = i + 1
    # right = (length of arr) - 1
    left, right = i + 1, len(arr) - 1
    
    while left < right:
      trips = arr[i] + arr[left] + arr[right]

      if trips < 0:
        left += 1 # increment the left
      
      elif trips > 0:
        right -= 1 # decrement the right

      else:
        # pushes the solution triplet to the list
        triplets.append([arr[i], arr[left], arr[right]])

        while (left < right) and arr[left] == arr[left+1]:
          left += 1

        while (left > right) and arr[left] == arr[right-1]:
          right += 1

        left += 1 # increment the left
        right -= 1 # decrement the right
      
  return triplets

data = [-1, 0, 1, 2, -1, -4]
trips = threeSum(data)

for trip in trips:
  print(trip)
