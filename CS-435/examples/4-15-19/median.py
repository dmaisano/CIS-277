# median of medians
# https://en.wikipedia.org/wiki/Median_of_medians
# https://www.youtube.com/watch?v=f_f9_GYcPSY

from math import ceil
from random import randint
from typing import List


def findMedian(arr: List[int], k=""):
    """Returns the median of an unsorted array

    Arguments:
        arr {List[int]} -- unsorted list of ints
        k {int} -- pivot index

    Returns:
        int -- median of the array
    """

    # pick random pivot
    if k == "":
        k = randint(1, len(arr))

    if len(arr) == 1:
        return arr[0]

    medianIndex = ceil(len(arr) / 2)

    # elements less than the pivot value
    left = []

    # elements greater than the pivot value
    right = []

    # filter the list O(n)
    for i in range(0, len(arr)):
        num = arr[i]

        # skip the pivot
        if i == k:
            continue

        if num < arr[k]:
            left.append(num)
        else:
            right.append(num)

    # found the median
    if len(left) + 1 == medianIndex:
        return arr[k]

    # # median exists somewhere in the left subarray
    # elif len(left) + 1 < medianIndex:
    #     return findMedian(left)

    # # median exists somewhere in the right subarray
    # else:
    #     return findMedian(right)

    # in this case, worst case sorting is O(n log n) ?


nums: List[int] = [7, 4, 18, -6, 1, 12, 14, 28, 19]

res = findMedian(nums)

print(res)
