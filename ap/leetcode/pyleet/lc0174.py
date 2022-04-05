#
# Author: montreal91
# Time: N/A
# Failed attempts: 3
#

import unittest


class Solution:
    def calculateMinimumHP(self, dungeon):
        DP = [[0 for _ in range(len(dungeon[0]))] for _ in range(len(dungeon))]

        DP[-1][-1] = max(1, 1 - dungeon[-1][-1])

        # fill right column
        for i in reversed(range(len(dungeon) - 1)):
            DP[i][-1] = max(DP[i+1][-1] - dungeon[i][-1], 1)

        # fill bottom row
        for j in reversed(range(len(dungeon[-1]) - 1)):
            DP[-1][j] = max(DP[-1][j+1] - dungeon[-1][j], 1)

        for i in reversed(range(len(dungeon) - 1)):
            for j in reversed(range(len(dungeon[i]) - 1)):
                DP[i][j] = min(
                    max(DP[i+1][j] - dungeon[i][j], 1),
                    max(DP[i][j+1] - dungeon[i][j], 1)
                )
        return DP[0][0]


class SolutionTestCase(unittest.TestCase):
    def tests_lc(self):
        dungeon0 = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
        self.assertEqual(Solution().calculateMinimumHP(dungeon0), 7)

        dungeon1 = [[0]]
        self.assertEqual(Solution().calculateMinimumHP(dungeon1), 1)

    def test_errors(self):
        dungeon0 = [[1,-2,3],[2,-2,-2]]
        self.assertEqual(Solution().calculateMinimumHP(dungeon0), 2)

        dungeon1 = [[2,1],[1,-1]]
        self.assertEqual(Solution().calculateMinimumHP(dungeon1), 1)

        dungeon2 = [[1,-3,3],[0,-2,0],[-3,-3,-3]]
        self.assertEqual(Solution().calculateMinimumHP(dungeon2), 3)


if __name__ == "__main__":
    unittest.main()
