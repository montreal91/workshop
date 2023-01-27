# 04:38
# 04:53

class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid):
        res = [[0 for _ in obstacleGrid[0]] for _ in obstacleGrid]

        if obstacleGrid[0][0] == 0:
            res[0][0] = 1

        for i in range(len(obstacleGrid)):
            for j in range(len(obstacleGrid[i])):
                if i == j == 0:
                    continue
                if obstacleGrid[i][j] == 1:
                    res[i][j] = 0
                    continue
                res[i][j] = res[i-1][j] + res[i][j-1]

        # for line in res:
        #     print(line)

        return res[-1][-1]



a1 = [
    [0, 0, 0],
    [0, 1, 0],
    [0, 0, 0]
]

a2 = [
    [0, 1],
    [0, 0]
]

a3 = [
    [0,0,0],
    [0,0,1],
    [0,1,0]
]

a4 = [
    [0, 1, 1, 0],
    [0, 1, 1, 0],
    [0, 0, 0, 0]
]

if __name__ == "__main__":
    assert Solution().uniquePathsWithObstacles(a1) == 2
    assert Solution().uniquePathsWithObstacles(a2) == 1
    assert Solution().uniquePathsWithObstacles(a3) == 0
    assert Solution().uniquePathsWithObstacles(a4) == 1
    print("All tests passed.")
