#
# Author: montreal91
# Time: N/A
# Failed attempts: 0
#

import unittest


class Solution:
    def maxProduct(self, nums):
        return max(self._solve(nums), self._solve(list(reversed(nums))))

    def _solve(self, nums):
        DP = [-10 for _ in range(len(nums))]

        prod = 0
        for i, numsi in enumerate(nums):
            if prod == 0:
                prod = 1
            prod *= numsi
            DP[i] = max(DP[i-1], prod)


        return max(DP)


class SolutionTest(unittest.TestCase):
    def test_all(self):
        self.assertEqual(Solution().maxProduct([2, 3, -2, 4]), 6)
        self.assertEqual(Solution().maxProduct([-2, 0, -1]), 0)
        self.assertEqual(Solution().maxProduct([2, -2, 2, 0, -2, 2, 2, -2, 0, 2]), 16)
        self.assertEqual(Solution().maxProduct([-2]), -2)
        self.assertEqual(Solution().maxProduct([-2, -2, -2]), 4)
        self.assertEqual(Solution().maxProduct([-2, -5, -5]), 25)
        self.assertEqual(Solution().maxProduct([1, 2, -3, 4, -5, 1, -2, 4]), 160)
        self.assertEqual(Solution().maxProduct([1, 2, -3, 4, -5, 1, -2, 4, 0, 1, 2, -3, 4, -5, 1, -2, 3]), 160)


if __name__ == "__main__":
    unittest.main()
