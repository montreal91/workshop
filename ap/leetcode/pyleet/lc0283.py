#
# Author: montreal91
# Time: 0:26
# Failed attempts: 0
#

class Solution:
    def moveZeroes(self, nums):
        """
        Do not return anything, modify nums in-place instead.
        """

        for i, _ in enumerate(nums):
            z = i + 1
            while z < len(nums) and nums[z] == 0:
                z += 1

            if z >= len(nums):
                continue
            if nums[i] == 0:
                nums[i], nums[z] = nums[z], nums[i]


if __name__ == '__main__':
    s = Solution()
    a1 = [0,1,0,3,12]
    s.moveZeroes(a1)
    assert a1 == [1, 3, 12, 0, 0]

    a2 = [0]
    s.moveZeroes(a2)
    assert a2 == [0]

    a3 = [1, 2, 3, 0, 0, 0]
    s.moveZeroes(a3)
    assert a3 == [1, 2, 3, 0, 0, 0]

    a4 = [1, 0, 0, 0, 2, 0, 0, 3, 0]
    s.moveZeroes(a4)
    assert a4 == [1, 2, 3, 0, 0, 0, 0, 0, 0]

    a5 = [0, 0, 0]
    s.moveZeroes(a5)
    assert a5 == [0, 0, 0]

    a6 = [1, 2, 3]
    s.moveZeroes(a6)
    assert a6 == [1, 2, 3]


    print("All tests passed.")
