# median of medians
# https://en.wikipedia.org/wiki/Median_of_medians
# https://www.youtube.com/watch?v=f_f9_GYcPSY

# really good example
# https://rcoh.me/posts/linear-time-median-finding/

from random import choice
from typing import List


def quickselect_median(arr: List[int], pivot_func=choice):

    if len(arr) % 2 == 1:
        return quickselect(arr, len(arr), pivot_func)
    else:
        return 0.5 * (
            quickselect(arr, len(arr) / 2 - 1, pivot_func)
            + quickselect(arr, len(arr) / 2, pivot_func)
        )


def quickselect(arr: List[int], k: int, pivot_func: object):
    """Select the k-th element in the arr (0 based)

    Arguments:
        arr {List[int]} -- List of ints
        k {int} -- Index
        pivot_func {object} -- Function to choose a pivot, defaults to random.choice

    Returns:
        [int] -- return the median of the array
    """

    # only one elem in arr
    if len(arr) == 1:
        assert k == 0
        return arr[0]

    pivot = pivot_func(arr)

    left = [num for num in arr if num < pivot]
    right = [num for num in arr if num > pivot]
    pivots = [num for num in arr if num == pivot]

    if k < len(left):
        return quickselect(left, k, pivot_func)

    # got lucky and guessed the median
    elif k < len(left) + len(pivots):
        return pivots[0]

    else:
        return quickselect(right, k - len(left) - len(pivots), pivot_func)

def pickPivot(arr: List[int]):
    """
    Pick a good pivot within the array
    This will run in O(n) time
    """

    asset len(arr) > 0

    # sort in nlogn time
    if len(arr) < 5:
        arr = sorted(arr)
         if len(arr) % 2 == 1:
             return arr[len(arr) / 2]
        else:
            return 0.5 *( arr[len(arr) / 2 - 1] +  arr[len(arr) / 2])



nums = [7, 4, 18, -6, 1, 12, 14, 28, 19]
res = quickselect_median(nums)
print(res)
