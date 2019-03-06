import unittest
from two_sum import twoSum


class TestTwoSum(unittest.TestCase):
    def test_sum_1(self):
        self.assertEqual(twoSum([1, 2, 3, 5, 10], 8), [2, 3], "Should be [2, 3]")

    def test_sum_2(self):
        self.assertEqual(twoSum([2, 7, 11, 15], 9), [0, 1], "Should be [0,1]")


if __name__ == "__main__":
    print(unittest.main())
