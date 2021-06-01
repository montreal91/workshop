#
# Author: montreal91
# Time: 0:24
# Failed attempts: 0
#

class Solution:
    def maxSubArray(self, nums):
        dp = max(0, nums[0])
        best = dp
        max_n = nums[0]
        for i in range(1, len(nums)):
            dp = max(0, dp + nums[i])
            max_n = max(max_n, nums[i])
            best = max(best, dp)

        if max_n <= 0:
            return max_n
        return best


if __name__ == '__main__':
    s = Solution()

    assert s.maxSubArray([1]) == 1
    assert s.maxSubArray([-1, 1, -1]) == 1
    assert s.maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]) == 6
    assert s.maxSubArray([5, 4, -1, 7, 8]) == 23
    assert s.maxSubArray([5, 4, -10, 7, 8]) == 15
    assert s.maxSubArray([5, 6, -2, -2, 1, 2, 3]) == 13
    print("All tests passed.")
        