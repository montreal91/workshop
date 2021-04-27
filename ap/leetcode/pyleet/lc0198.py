#
# Author: montreal91
# Time: 0:14
# Failed attempts: 0
#

class Solution:
    def rob(self, nums):
        if len(nums) == 0:
            return 0
        if len(nums) == 1:
            return nums[0]

        D = [0 for _ in range(len(nums))]
        D[0] = nums[0]
        D[1] = max(D[0], nums[1])

        for i in range(2, len(nums)):
            D[i] = max(D[i-1], D[i-2]+nums[i])

        return D.pop()


if __name__ == '__main__':
    S = Solution()

    assert S.rob([]) == 0
    assert S.rob([12]) == 12
    assert S.rob([1, 2, 3, 1]) == 4
    assert S.rob([2, 7, 9, 3, 1]) == 12
    assert S.rob([1, 2]) == 2
    assert S.rob([1, 2, 3]) == 4
    assert S.rob([7, 8, 7, 8, 9, 8]) == 24
    assert S.rob([3,5,2,2,3,6,6,5,1]) == 18

    print("All tests passed.")
