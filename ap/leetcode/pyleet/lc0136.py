#
# Author: montreal91
# Time: N/A
# Failed attempts: N/A
#

class Solution:
    def singleNumber(self, nums):
        res = 0
        for n in nums:
            res ^= n
        return res


if __name__ == "__main__":
    s = Solution()

    assert s.singleNumber([1, 2, 3, 3, 2]) == 1
    assert s.singleNumber([1]) == 1
    assert s.singleNumber([2, 1, 2]) == 1
    assert s.singleNumber([2, 5, 3, 4, 5, 4, 2, 3, 1]) == 1
    assert s.singleNumber([4, 1, 2, 1, 2]) == 4

    print("All tests passed.")
