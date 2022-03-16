#
# Author: montreal91
# Time: 0:20
# Failed attempts: 0
#

class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        DP = [[1 for _ in range(n)] for _ in range(m)]
        for i in range(1, m):
            for j in range(1, n):
                DP[i][j] = DP[i-1][j] + DP[i][j-1]
        return DP[m-1][n-1]

    def _print_dp(self, dp):
        for line in dp:
            print(line)


if __name__ == "__main__":
    assert Solution().uniquePaths(1, 1) == 1
    assert Solution().uniquePaths(1, 5) == 1
    assert Solution().uniquePaths(2, 5) == 5
    assert Solution().uniquePaths(3, 5) == 15
    assert Solution().uniquePaths(5, 3) == 15
    assert Solution().uniquePaths(3, 7) == 28
    assert Solution().uniquePaths(3, 2) == 3

    print("All tests passed.")
