
class Solution:
    def superEggDrop(self, k: int, n: int) -> int:
        D = [[0 for _ in range(n+1)] for _ in range(k + 1)]

        for i in range(k+1):
            D[i][0] = 0
            D[i][1] = 1

        for j in range(n+1):
            D[1][j] = j

        for i in range(2, k+1):
            for j in range(2, n+1):
                D[i][j] = 1000000
                for l in range(1, j):
                    test = max(D[i-1][l-1], D[i][j-l])
                    D[i][j] = min(D[i][j], test)
                D[i][j] += 1

        return D[k][n]


def test():
    s = Solution()
    assert s.superEggDrop(k=1, n=10) == 10
    assert s.superEggDrop(k=2, n=10) == 4
    assert s.superEggDrop(k=3, n=14) == 4
    assert s.superEggDrop(k=3, n=100) == 9
    assert s.superEggDrop(k=4, n=2000) == 16
    print("All tests passed.")


if __name__ == '__main__':
    test()
