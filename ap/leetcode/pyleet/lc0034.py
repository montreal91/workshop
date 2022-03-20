#
# Author: montreal91
# Time: 1:10
# Failed attempts: 0
#

NO = [-1, -1]


class Solution:
    def searchRange(self, nums, target):
        if not nums:
            return NO

        res = [self._find_left_pos(nums, target), self._find_right_pos(nums, target)]
        return res

    def _find_left_pos(self, nums, target):
        left, right = 0, len(nums) - 1

        while left < right:
            mid = (left + right) // 2

            if nums[mid] == target:
                if mid == 0 or nums[mid - 1] < target:
                    return mid
                else:
                    right = mid - 1
                    continue

            if nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1

        if nums[left] == target:
            return left
        return -1

    def _find_right_pos(self, nums, target):
        left, right = 0, len(nums) - 1

        while left < right:
            mid = (left + right) // 2
            if nums[mid] == target:
                if mid == len(nums) - 1 or nums[mid + 1] > target:
                    return mid
                else:
                    left = mid + 1
                    continue

            if nums[mid] > target:
                right = mid - 1
            else:
                left = mid + 1

        if nums[left] == target:
            return left
        return -1


def smoke_test():
    nums_leet = [5, 7, 7, 8, 8, 10]
    assert Solution().searchRange(nums=[], target=8) == [-1, -1]

    assert Solution().searchRange(nums=nums_leet, target=6) == [-1, -1]
    assert Solution().searchRange(nums=nums_leet, target=8) == [3, 4]
    assert Solution().searchRange(nums=nums_leet, target=5) == [0, 0]
    assert Solution().searchRange(nums=nums_leet, target=10) == [5, 5]
    assert Solution().searchRange(nums=nums_leet, target=7) == [1, 2]

    assert Solution().searchRange(nums=[1, 1], target=1) == [0, 1]
    assert Solution().searchRange(nums=[1, 1, 1], target=1) == [0, 2]
    assert Solution().searchRange(nums=[1, 1, 1, 1], target=1) == [0, 3]
    assert Solution().searchRange(nums=[1, 1, 1, 1, 1], target=1) == [0, 4]

    my_nums_even = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    my_nums_odd = [1, 2, 3, 4, 5, 6, 7, 8, 9]

    assert  Solution().searchRange(nums=my_nums_even, target=1) == [0, 0]
    assert  Solution().searchRange(nums=my_nums_even, target=2) == [1, 1]
    assert  Solution().searchRange(nums=my_nums_even, target=3) == [2, 2]
    assert  Solution().searchRange(nums=my_nums_even, target=4) == [3, 3]
    assert  Solution().searchRange(nums=my_nums_even, target=5) == [4, 4]
    assert  Solution().searchRange(nums=my_nums_even, target=6) == [5, 5]
    assert  Solution().searchRange(nums=my_nums_even, target=7) == [6, 6]
    assert  Solution().searchRange(nums=my_nums_even, target=8) == [7, 7]
    assert  Solution().searchRange(nums=my_nums_even, target=9) == [8, 8]
    assert  Solution().searchRange(nums=my_nums_even, target=10) == [9, 9]
    assert  Solution().searchRange(nums=my_nums_even, target=11) == [-1, -1]
    assert  Solution().searchRange(nums=my_nums_even, target=0) == [-1, -1]

    assert  Solution().searchRange(nums=my_nums_odd, target=1) == [0, 0]
    assert  Solution().searchRange(nums=my_nums_odd, target=2) == [1, 1]
    assert  Solution().searchRange(nums=my_nums_odd, target=3) == [2, 2]
    assert  Solution().searchRange(nums=my_nums_odd, target=4) == [3, 3]
    assert  Solution().searchRange(nums=my_nums_odd, target=5) == [4, 4]
    assert  Solution().searchRange(nums=my_nums_odd, target=6) == [5, 5]
    assert  Solution().searchRange(nums=my_nums_odd, target=7) == [6, 6]
    assert  Solution().searchRange(nums=my_nums_odd, target=8) == [7, 7]
    assert  Solution().searchRange(nums=my_nums_odd, target=9) == [8, 8]
    assert  Solution().searchRange(nums=my_nums_odd, target=10) == [-1, -1]
    assert  Solution().searchRange(nums=my_nums_odd, target=0) == [-1, -1]

    print("All tests passed")


if __name__ == "__main__":
    smoke_test()
