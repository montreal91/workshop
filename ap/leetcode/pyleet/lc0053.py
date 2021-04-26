#
# Author: montreal91
# Time: N/A
# Failed attempts: 1
#

class Solution:
    def maxSubArray(self, nums):

        best = nums[0]
        D = [nums[0] for _ in nums]
        for i in range(1, len(nums)):
            D[i] = max(D[i-1] + nums[i], nums[i])
            best = max(best, D[i])
        return best


def test():
    s = Solution()
    assert s.maxSubArray([-1]) == -1
    assert s.maxSubArray([-5, -6, -7, -8, -2]) == -2
    assert s.maxSubArray([1, 2, 3]) == 6
    assert s.maxSubArray([1, 2, -4, 1, 2, 3, -1, -1, -1, -1, -3, 4]) == 6

    # leet cases
    assert s.maxSubArray([-2,1,-3,4,-1,2,1,-5,4]) == 6
    assert s.maxSubArray([1]) == 1
    assert s.maxSubArray([5,4,-1,7,8]) == 23
    assert s.maxSubArray([-2, 1]) == 1
    print("All tests passed.")


if __name__ == '__main__':
    test()
