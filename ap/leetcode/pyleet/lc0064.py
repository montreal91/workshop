#
# Author: montreal91
# Time: 0:40
# Failed attempts: 1
#

import unittest


class Solution:
    def minPathSum(self, grid):
        dp = [[grid[0][0] for _ in range(len(grid[0]))] for _ in range(len(grid))]

        for j in range(1, len(grid[0])):
            dp[0][j] = dp[0][j-1] + grid[0][j]

        for i in range(1, len(grid)):
            dp[i][0] = dp[i-1][0] + grid[i][0]

        for i in range(1, len(grid)):
            for j in range(1, len(grid[0])):
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]

        return dp[-1][-1]


class SolutionTestCase(unittest.TestCase):
    def test_solution(self):
        self.assertEqual(1, Solution().minPathSum([[1]]))
        self.assertEqual(7, Solution().minPathSum([[1, 3, 1], [1, 5, 1], [4, 2, 1]]))
        self.assertEqual(14, Solution().minPathSum([[1, 4, 4, 1, 0],[5, 10, 0, 2, 3],[0, 3, 3, 1, 2]]))
        self.assertEqual(12, Solution().minPathSum([[1,2,3],[4,5,6]]))

        rand1 = [
            [2, 4, 8, 2, 2],
            [1, 9, 10, 3, 9],
            [3, 6, 2, 9, 8],
            [1, 4, 10, 10, 6],
            [10, 5, 8, 7, 9]
        ]
        self.assertEqual(40, Solution().minPathSum(rand1))

        rand2 = [
            [7, 4, 5, 3, 2, 1, 10, 3],
            [5, 8, 3, 3, 0, 9, 10, 2],
            [3, 5, 2, 7, 5, 7, 0, 2]
        ]
        self.assertEqual(35, Solution().minPathSum(rand2))

        rand3 = [
            [10, 0, 0, 7, 8, 0],
            [5, 8, 8, 8, 6, 3],
            [1, 6, 5, 1, 1, 4],
            [7, 2, 1, 10, 6, 6]
        ]
        self.assertEqual(35, Solution().minPathSum(rand3))

        self.assertEqual(0, Solution().minPathSum([[0]]))
        self.assertEqual(3, Solution().minPathSum([[0, 1, 2]]))
        self.assertEqual(3, Solution().minPathSum([[0], [1], [2]]))


if __name__ == "__main__":
    unittest.main()