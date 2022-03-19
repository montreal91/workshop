#
# Author: montreal91
# Time: 1:40
# Failed attempts: 0
#

MAX = 100000000


class Solution:
    def preimageSizeFZF(self, k) -> int:
        if k == 0:
            return 5
        left, right = 0, MAX * MAX

        while left < right:
            mid = (left + right) // 2
            val = self.trailingZeroes(mid)

            if val == k:
                return 5

            if val < k:
                left = mid + 1
            elif val > k:
                right = mid - 1
            else:
                return -1
        return 0

    def trailingZeroes(self, n):
        if n == 0:
            return 1
        five = 5
        res = 0
        while five <= n:
            res += n // five
            five *= 5
        return res


if __name__ == "__main__":
    assert Solution().preimageSizeFZF(2)  == 5
    assert Solution().preimageSizeFZF(3)  == 5
    assert Solution().preimageSizeFZF(4)  == 5
    assert Solution().preimageSizeFZF(5)  == 0
    assert Solution().preimageSizeFZF(6)  == 5
    assert Solution().preimageSizeFZF(7)  == 5
    assert Solution().preimageSizeFZF(8)  == 5
    assert Solution().preimageSizeFZF(9)  == 5
    assert Solution().preimageSizeFZF(10) == 5
    assert Solution().preimageSizeFZF(11) == 0
    assert Solution().preimageSizeFZF(12) == 5
    assert Solution().preimageSizeFZF(13) == 5
    assert Solution().preimageSizeFZF(14) == 5
    assert Solution().preimageSizeFZF(15) == 5
    assert Solution().preimageSizeFZF(16) == 5
    assert Solution().preimageSizeFZF(17) == 0
    assert Solution().preimageSizeFZF(18) == 5
    assert Solution().preimageSizeFZF(19) == 5
    assert Solution().preimageSizeFZF(20) == 5
    assert Solution().preimageSizeFZF(21) == 5
    assert Solution().preimageSizeFZF(22) == 5
    assert Solution().preimageSizeFZF(23) == 0
    assert Solution().preimageSizeFZF(24) == 5
    assert Solution().preimageSizeFZF(25) == 5
    assert Solution().preimageSizeFZF(26) == 5
    assert Solution().preimageSizeFZF(27) == 5

    assert Solution().preimageSizeFZF(28) == 5
    assert Solution().preimageSizeFZF(29) == 0
    assert Solution().preimageSizeFZF(30) == 0
    assert Solution().preimageSizeFZF(31) == 5

    assert Solution().preimageSizeFZF(59) == 5
    assert Solution().preimageSizeFZF(60) == 0
    assert Solution().preimageSizeFZF(61) == 0
    assert Solution().preimageSizeFZF(62) == 5

    assert Solution().preimageSizeFZF(152) == 5
    assert Solution().preimageSizeFZF(153) == 0
    assert Solution().preimageSizeFZF(154) == 0
    assert Solution().preimageSizeFZF(155) == 0
    assert Solution().preimageSizeFZF(156) == 5

    assert Solution().preimageSizeFZF(208) == 5
    assert Solution().preimageSizeFZF(209) == 5
    assert Solution().preimageSizeFZF(210) == 0
    assert Solution().preimageSizeFZF(211) == 5
    assert Solution().preimageSizeFZF(212) == 5

    assert Solution().preimageSizeFZF(100000000) == 5

    print("All tests passed.")
