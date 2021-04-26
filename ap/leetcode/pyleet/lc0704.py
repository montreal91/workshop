#
# Author: montreal91
# Time: 0:23
# Failed attempts: 0
#


class Solution:
    def search(self, nums, target):
        left = 0
        right = len(nums) - 1

        while left <= right:
            i = (left + right) // 2
            if target == nums[i]:
                return i

            if target > nums[i]:
                left = i + 1
            if target < nums[i]:
                right = i - 1

        return -1


if __name__ == '__main__':
    s = Solution()
    a1 = [-1,0,3,5,9,12]
    a0 = [3]
    a16 = [i * 2 for i in range(1, 17)]

    assert s.search(a1, 9) == 4
    assert s.search(a0, 3) == 0
    assert s.search(a0, 4) == -1
    assert s.search(a1, -1) == 0
    assert s.search(a1, 12) == 5
    assert s.search(a1, 0) == 1
    assert s.search(a1, 3) == 2
    assert s.search(a1, 5) == 3
    assert s.search(a1, 13) == -1
    assert s.search(a1, 6) == -1
    assert s.search(a16, 9) == -1
    assert s.search(a16, 12) == 5

    print("All tests passed.")
