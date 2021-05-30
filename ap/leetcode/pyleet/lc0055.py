#
# Author: montreal91
# Time: 0:26
# Failed attempts: 1
#

class Solution:
    def canJump(self, nums):
        good = len(nums)

        for i in reversed(range(len(nums))):
            jump = nums[i]
            if good - i <= jump:
                good = i
        return good == 0


if __name__ == '__main__':
    s = Solution()

    assert s.canJump([0]) == False
    assert s.canJump([1]) == True
    assert s.canJump([0, 1]) == False
    assert s.canJump([1, 0]) == False
    assert s.canJump([1, 1]) == True
    assert s.canJump([1, 2, 0, 0, 1, 1]) == False
    assert s.canJump([1, 3, 0, 0, 1, 1]) == True

    assert s.canJump([1, 1, 3, 0, 0, 2, 0, 1]) == True


    print("All tests passed.")
