#
# Author: montreal91
# Solved in 0:20
# Failed attempts: 0
#

class Solution:
    def climbStairs(self, n):
        if 0 <= n <= 2:
            return n

        D = [0 for _ in range(n)]
        D[0] = 1
        D[1] = 2

        for i in range(2, n):
            D[i] = D[i-1] + D[i-2]

        return D.pop()


def test():
    s = Solution()
    assert s.climbStairs(1) == 1
    assert s.climbStairs(2) == 2
    assert s.climbStairs(3) == 3
    assert s.climbStairs(4) == 5
    assert s.climbStairs(5) == 8
    assert s.climbStairs(6) == 13
    print("All tests passed.")


if __name__ == '__main__':
    test()
