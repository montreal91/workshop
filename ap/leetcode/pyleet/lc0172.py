#
# Author: montreal91
# Time: 0:30
# Failed attempts: 0
#

class Solution:
    def trailingZeroes(self, n):
        five = 5
        res = 0
        while five <= n:
            res += n // five
            five *= 5
        return res


if __name__ == "__main__":
    assert Solution().trailingZeroes(0)  == 0
    assert Solution().trailingZeroes(1)  == 0
    assert Solution().trailingZeroes(2)  == 0
    assert Solution().trailingZeroes(3)  == 0
    assert Solution().trailingZeroes(4)  == 0
    assert Solution().trailingZeroes(5)  == 1
    assert Solution().trailingZeroes(6)  == 1
    assert Solution().trailingZeroes(7)  == 1
    assert Solution().trailingZeroes(8)  == 1
    assert Solution().trailingZeroes(9)  == 1
    assert Solution().trailingZeroes(10) == 2
    assert Solution().trailingZeroes(11) == 2
    assert Solution().trailingZeroes(12) == 2
    assert Solution().trailingZeroes(13) == 2
    assert Solution().trailingZeroes(14) == 2
    assert Solution().trailingZeroes(15) == 3
    assert Solution().trailingZeroes(16) == 3
    assert Solution().trailingZeroes(17) == 3
    assert Solution().trailingZeroes(18) == 3
    assert Solution().trailingZeroes(19) == 3
    assert Solution().trailingZeroes(20) == 4
    assert Solution().trailingZeroes(21) == 4
    assert Solution().trailingZeroes(22) == 4
    assert Solution().trailingZeroes(23) == 4
    assert Solution().trailingZeroes(24) == 4
    assert Solution().trailingZeroes(25) == 6
    assert Solution().trailingZeroes(26) == 6
    assert Solution().trailingZeroes(27) == 6
    assert Solution().trailingZeroes(28) == 6
    assert Solution().trailingZeroes(29) == 6
    assert Solution().trailingZeroes(30) == 7
    assert Solution().trailingZeroes(999) == 246
    assert Solution().trailingZeroes(1000) == 249
    assert Solution().trailingZeroes(9999) == 2495
    assert Solution().trailingZeroes(10000) == 2499

    print("All tests passed.")
