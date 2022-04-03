#
# Author: montreal91
# Time: 0:30
# Failed attempts: 0
#

import unittest

MIN = - 2 ** 31


class Solution:
    def findPeakElement(self, nums):
        mnts = [MIN] + nums + [MIN]
        il = 0
        ir = len(mnts) - 1

        while il < ir:
            im = (il + ir) // 2

            if mnts[im - 1] < mnts[im] and mnts[im] > mnts[im + 1]:
                return im - 1

            if mnts[im - 1] <= mnts[im]:
                il = im
            else:
                ir = im

        return -1


class SolutionTestCase(unittest.TestCase):
    def test_leet(self):
        self.assertEqual(2, Solution().findPeakElement([1,2,3,1]))
        self.assertTrue(Solution().findPeakElement([1,2,1,3,5,6,4]) in {1, 2, 5})

    def test_corner(self):
        self.assertEqual(0, Solution().findPeakElement([-10]))
        self.assertEqual(0, Solution().findPeakElement([-10, -11]))
        self.assertEqual(1, Solution().findPeakElement([2, 3]))

        self.assertEqual(0, Solution().findPeakElement([3, 2, 1]))
        self.assertEqual(1, Solution().findPeakElement([2, 3, 2]))
        self.assertEqual(2, Solution().findPeakElement([1, 2, 3]))

        self.assertEqual(0, Solution().findPeakElement([0, -1, -2, -3]))
        self.assertEqual(1, Solution().findPeakElement([-1, 0, -2, -3]))
        self.assertEqual(2, Solution().findPeakElement([-2, -1, 0, -3]))
        self.assertEqual(3, Solution().findPeakElement([-3, -2, -1, 0]))

    def test_random(self):
        nums1 = [-6, -3, 2, -10, -8, -1, -3, -2, 9, -3, 9, 10, -3, 5, 9, -3, 10, -7, 6, -4]
        self.assertTrue(Solution().findPeakElement(nums1) in {0, 2, 5, 8, 11, 14, 16})



if __name__ == "__main__":
    unittest.main()
