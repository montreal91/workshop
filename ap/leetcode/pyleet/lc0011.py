#
# Author: montreal91
# Time: 0:40
# Failed attempts: 0
#

import unittest


class Solution:
    def maxArea(self, height):
        left_good = [0 for _ in height]
        right_good = [0 for _ in height]

        left_good[0] = height[0]
        for i in range(1, len(height)):
            left_good[i] = max(left_good[i-1], height[i])

        right_good[-1] = height[-1]
        for i in reversed(range(0, len(height)-1)):
            right_good[i] = max(right_good[i+1], height[i])

        res = 0
        i, j = 0, len(height) - 1

        while i < j:
            water = min(left_good[i], right_good[j]) * (j - i)
            res = max(res, water)

            if left_good[i] < right_good[j]:
                i += 1
            else:
                j -= 1

        return res


class SolutionTestCase(unittest.TestCase):
    def test_solution(self):
        self.assertEquals(56, Solution().maxArea([0, 10, 5, 3, 10, 4, 4, 7, 8, 4]))
        self.assertEquals(42, Solution().maxArea([0, 5, 6, 1, 5, 7, 7, 2, 3, 10]))
        self.assertEquals(49, Solution().maxArea([4, 7, 3, 9, 3, 8, 1, 7, 9, 2]))

    def test_leet(self):
        self.assertEquals(49, Solution().maxArea([1,8,6,2,5,4,8,3,7]))
        self.assertEquals(1, Solution().maxArea([1,1]))

if __name__ == "__main__":
    unittest.main()