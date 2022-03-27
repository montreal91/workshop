#
# Author: montreal91
# Time: 2:30
# Failed attempts: 0
#

import unittest


class Solution:
    def firstMissingPositive(self, nums):
        for i, _ in enumerate(nums):
            if nums[i] <= 0 or nums[i] > len(nums):
                nums[i] = -1

        for i, n in enumerate(nums):
            if n < 0 or i == n:
                continue
            if n < i:
                nums[n] = n
            else:
                self._do_swaps(i, nums)

        for i in range(1, len(nums)):
            if nums[i] != i:
                return i

        if nums[0] == 0:
            return len(nums) + 1
        return len(nums)


    def _do_swaps(self, i, nums):
        need_proceed = True
        while need_proceed:
            n = nums[i] % len(nums)
            ni = nums[n]

            # swap itself
            nums[i], nums[n] = nums[n], n

            if i == nums[i]:
                need_proceed = False
            elif n == ni:
                nums[i] = -1
                need_proceed = False
            elif nums[i] < 0:
                need_proceed = False



class SolutionTest(unittest.TestCase):
    def test_solution1(self):
        nums = [1, 2, -3, 4, 5, 8]
        self.assertEqual(3, Solution().firstMissingPositive(nums))

    def test_solution2(self):
        nums = [9, 8, 2, 7, 3, 1, 6, 4, 12, 5]
        self.assertEqual(10, Solution().firstMissingPositive(nums))

    def test_solution3(self):
        nums = [3, 6, 5, 7, 9, 9, -4, 3, 7, 5]
        self.assertEqual(1, Solution().firstMissingPositive(nums))

    def test_solution4(self):
        nums = [1, 2, 0]
        self.assertEqual(3, Solution().firstMissingPositive(nums))

    def test_solution5(self):
        nums = [3, 1, 2]
        self.assertEqual(4, Solution().firstMissingPositive(nums))

    def test_solution6(self):
        nums = [1]
        self.assertEqual(2, Solution().firstMissingPositive(nums))

    def test_solution7(self):
        nums = [-1]
        self.assertEqual(1, Solution().firstMissingPositive(nums))

    def test_solution7(self):
        nums = [10]
        self.assertEqual(1, Solution().firstMissingPositive(nums))

    def test_solution8(self):
        nums = [3,4,-1,1]
        self.assertEqual(2, Solution().firstMissingPositive(nums))

    def test_solution9(self):
        nums = [7,8,9,11,12]
        self.assertEqual(1, Solution().firstMissingPositive(nums))


if __name__ == "__main__":
    unittest.main()
