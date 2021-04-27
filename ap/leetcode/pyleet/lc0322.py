#
# Author: montreal91
# Time: 0:15
# Failed attempts: 0
#

INTMAX = 2 ** 31 - 1

class Solution:
    def coinChange(self, coins, amount):
        coins.sort()

        D = [INTMAX for _ in range(amount+1)]
        D[0] = 0

        for i in range(1, amount + 1):
            for c in coins:
                if c > i:
                    break
                D[i] = min(D[i], D[i-c] + 1)

        res = D.pop()
        if res == INTMAX:
            return -1
        return res


if __name__ == '__main__':
    S = Solution()

    assert S.coinChange([1], 0) == 0
    assert S.coinChange([1], 1) == 1
    assert S.coinChange([1], 2) == 2
    assert S.coinChange([2], 1) == -1
    assert S.coinChange([2], 2) == 1
    assert S.coinChange([2], 3) == -1

    assert S.coinChange(coins = [1,2,5], amount = 11) == 3

    print("All tests passed.")
